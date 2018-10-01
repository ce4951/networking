library ieee;
use ieee.std_logic_1164.all;

entity channel_monitor is 
port(
	RST_n, CLK, RX	: in std_logic;
	IDLE, BUSY, COLLISION: out std_logic
);
end entity channel_monitor;

architecture BEHAVIORAL of channel_monitor is

	signal interrupt_n 	: std_logic;
	signal reset_n 	 	: std_logic;
	signal reset_timer_n : std_logic;
	signal last_RX			: std_logic;
	signal state 		 	: std_logic_vector(1 downto 0);

	component interrupt_timer 
	generic (
		timeNS: Integer := 100000000;
		masterClkPeriodNS: Integer := 20						--50 MHz clock = 20 ns period
	);
	
	port(
		rst_n, clk: 	in std_logic;
		interrupt_n: 	out std_logic
	);
	end component;
	
	component state_machine port(
		RST_n, CLK : in std_logic;
		RX, INT_n  : in std_logic;

      STATE : out std_logic_vector(1 downto 0)
	);
	end component;
	
	begin
		U1 : interrupt_timer
			generic map (
				timeNS => 1110000,
				masterClkPeriodNS => 20
			)
			
			port map (
				rst_n => reset_n,
				clk 	=> CLK,
				interrupt_n => interrupt_n
			);
		
		U2 : state_machine
			port map(
				RST_n => RST_n,
				CLK => CLK,
				RX => RX,
				INT_n => interrupt_n,
				STATE => state
			);
			
		reset_timer : process(CLK) is
			variable toggle : boolean := false;
		begin
			if rising_edge(CLK) then
				if interrupt_n = '0' or RX /= last_RX then
					reset_timer_n <= '0';
					toggle := true;
				elsif toggle then
					reset_timer_n <= '1';
					toggle := false;
				end if;
				
				last_RX <= RX;
			end if;
		end process;
		
		reset_n <= reset_timer_n and RST_n;
		
		IDLE <= '1' 		when state = "00" else '0';
		BUSY <= '1' 		when state = "01" else '0';
		COLLISION <= '1' 	when state = "10" else '0';
end architecture BEHAVIORAL;