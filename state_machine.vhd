
-- IDLE = state 0, BUSY = state 1, COLLISION = state 2

library ieee;
use ieee.std_logic_1164.all;
--use ieee.std_logic_unsigned.all;

-- Inputs and outputs of the state machine
entity state_machine is
port( -- Inputs - reset for testing, clock signal to advance state, and
      -- reciver signal and timer signal for next state logic
      RST, CLK  : in std_logic;
      RX, TIMER : in std_logic;

      -- Outputs - current state to send to the top level for output
      STATE : out std_logic_vector(1 downto 0));
end entity state_machine;

-- State machine logic
architecture behavioral of state_machine is
    -- Possible state outputs with aliases
    type STATES is (IDLE, BUSY, COLL);

    -- Current and next state signals
    signal D : STATES := IDLE;
    signal Q : STATES := IDLE;

    -- Signals to determine if there is an edge from the receiver signal
    signal RX_CHANGED : std_logic := '0';
    signal PREV_RX    : std_logic := '1';

    -- Begin state machine logic
    begin
      -- Next state logic
      D <= IDLE when Q=BUSY and TIMER='1' and RX='1' else
           BUSY when Q=IDLE and RX_CHANGED='1'       else
           BUSY when Q=COLL and RX_CHANGED='1'       else
           COLL when Q=BUSY and TIMER='1' and RX='0' else
           IDLE;

    -- Next state memory
    NEXTSTATE: process(RST, CLK)
    begin
      if RST='0'             then Q<=IDLE;
      elsif rising_edge(CLK) then Q<=D;
      end if;
    end process;

    -- Processes to determine if receiver signal changed.
    --
    -- Signal is set to detect a change when a rising edge from the clock occurs and
    -- the receiver signal changed from last clock period.
    CHANGE: process(CLK, RX)
    begin
      if rising_edge(CLK) then
        if RX /= PREV_RX then RX_CHANGED<='1';
        else RX_CHANGED<='0';
        end if;

      PREV_RX<=RX;
      end if;
    end process;

    -- Output logic. IDLE = state 0, BUSY = state 1, COLLISION = state 2, invalid state = state 3
    with Q select
      STATE <= b"00" when IDLE,
               b"01" when BUSY,
               b"10" when COLL,
               b"11" when others;
end architecture behavioral;