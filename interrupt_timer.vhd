-- Timer

library ieee;
use ieee.std_logic_1164.all;

entity interrupt_timer is
generic (
	timeNS: Integer := 100000000;
	masterClkPeriodNS: Integer := 20						--50 MHz clock = 20 ns period
);

port (
	rst_n, clk: 	in std_logic;
	interrupt_n: 	out std_logic
);
end entity interrupt_timer;

architecture behavioral of interrupt_timer is

begin

	timer: process(clk, rst_n) is
	variable cnt: Integer := 0;
	variable limit: Integer := timeNS / masterClkPeriodNS;
	
	begin
		--increment count value on rising edge or reset count on reset signal
		if rst_n = '0' then
			cnt := 0;
		elsif rising_edge(clk) then
			if cnt < limit-1 then
				cnt := cnt + 1;
			end if;
		end if;
		
		--set interrupt to 0 if the count limit has been reached; otherwise 1
		if cnt = limit-1 then
			interrupt_n <= '0';
		else
			interrupt_n <= '1';
		end if;
	end process;
		

end architecture behavioral;
	
