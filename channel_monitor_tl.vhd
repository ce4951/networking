library ieee;
use ieee.std_logic_1164.all;

entity channel_monitor_tl is 
port(
	RST_n, CLK, RX	: in std_logic;
	IDLE, BUSY, COLLISION: out std_logic
);
end entity channel_monitor_tl;

architecture BEHAVIORAL of channel_monitor_tl is

	signal clock_signal : std_logic;

	component channel_monitor 
	port (
		RST_n, CLK, RX	: in std_logic;
		IDLE, BUSY, COLLISION: out std_logic
	);
	end component;
	
	component SLOWCLK port(
		RST, CLK50MHZ: in std_logic;
      CLK1HZ:  inout std_logic
	);
	end component;
	
	begin
		U1 : channel_monitor		
			port map (
				RST_n => RST_n,
				CLK 	=> clock_signal,
				RX => RX,
				IDle => IDLE,
				BUSY => BUSY,
				COLLISION => COLLISION
			);
		
		U2 : SLOWCLK
			port map(
				RST => RST_n,
				CLK50MHZ => CLK,
				CLK1HZ => clock_signal
			);
end architecture BEHAVIORAL;