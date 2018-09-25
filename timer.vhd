-- Timer

library ieee;
use ieee.std_logic_1164.all;

entity timer is
generic (
	timeNS: Integer := 1000000000;
	masterClkPeriodNS: Integer := 20						--50 MHz clock = 20 ns period
);

port (
	RST, CLK: 	in std_logic;
	interrupt: 	out std_logic
);
end entity timer;

architecture BEHAVIORAL of timer is

begin

	timer: process(CLK, RST) is
	variable cnt: Integer := 0;
	variable limit: Integer := timeNS / masterClkPeriodNS;
	
	begin
		--increment count value on rising edge or reset count on reset signal
		if RST = '0' then
			cnt := 0;
		elsif rising_edge(CLK) then
			cnt := cnt + 1;
		end if;
		
		--set interrupt to 0 if the count limit has been reached; otherwise 1
		if cnt = limit-1 then
			interrupt <= '0';
		else
			interrupt <= '1';
		end if;
	end process;
		

end architecture BEHAVIORAL;
	
