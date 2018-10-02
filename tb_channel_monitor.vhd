-- Copyright (C) 2018  Intel Corporation. All rights reserved.
-- Your use of Intel Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Intel Program License 
-- Subscription Agreement, the Intel Quartus Prime License Agreement,
-- the Intel FPGA IP License Agreement, or other applicable license
-- agreement, including, without limitation, that your use is for
-- the sole purpose of programming logic devices manufactured by
-- Intel and sold by Intel or its authorized distributors.  Please
-- refer to the applicable agreement for further details.

-- ***************************************************************************
-- This file contains a Vhdl test bench template that is freely editable to   
-- suit user's needs .Comments are provided in each section to help the user  
-- fill out necessary details.                                                
-- ***************************************************************************
-- Generated on "09/30/2018 18:19:32"
                                                            
-- Vhdl Test Bench template for design  :  channel_monitor
-- 
-- Simulation tool : ModelSim-Altera (VHDL)
-- 

LIBRARY ieee;                                               
USE ieee.std_logic_1164.all;                                

ENTITY tb_channel_monitor IS
END tb_channel_monitor;
ARCHITECTURE channel_monitor_arch OF tb_channel_monitor IS
-- constants
CONSTANT clk_period : time := 20000 ns;                                                 
-- signals                                                   
SIGNAL BUSY : STD_LOGIC;
SIGNAL CLK : STD_LOGIC := '0';
SIGNAL COLLISION : STD_LOGIC;
SIGNAL IDLE : STD_LOGIC;
SIGNAL RST_n : STD_LOGIC := '1';
SIGNAL RX : STD_LOGIC := '1';

COMPONENT channel_monitor
	PORT (
	BUSY : BUFFER STD_LOGIC;
	CLK : IN STD_LOGIC;
	COLLISION : BUFFER STD_LOGIC;
	IDLE : BUFFER STD_LOGIC;
	RST_n : IN STD_LOGIC;
	RX : IN STD_LOGIC
	);
END COMPONENT;
BEGIN
	i1 : channel_monitor
	PORT MAP (
-- list connections between master ports and signals
	BUSY => BUSY,
	CLK => CLK,
	COLLISION => COLLISION,
	IDLE => IDLE,
	RST_n => RST_n,
	RX => RX
	);

--test case 1 and 2
--continous_collision : PROCESS is
--begin
--	wait for 40000 ns;
--	RX <= '0';
--	
--	wait for 3 ms;
--	RX <= '1';
--	
--	wait;
--end process;


--test_case_3 : PROCESS is
--begin
--	RX <= '0';
--	wait for 500 ms; 
--	RX <= '1';
--	wait for 500 ms; 
--end process;
--
--test_case_4 : PROCESS is
--begin
--	RX <= '0';
--	wait for 1 ms; 
--	RX <= '1';
--	wait for 1 ms;
--end process;

--test_case_6 : PROCESS is
--begin
--	RX <= '1';
--	wait for 1 ms;
--	RX <= '0';
--	wait for 333.25 us;
--end process;

--test_case_8 : PROCESS is
--begin
--	RX <= '0';
--	wait for 1 ms;
--	RX <= '1';
--	wait for 333.25 us;
--end process;


always: PROCESS is
begin
	  clk <= '0';
	  wait for clk_period/2; 
	  clk <= '1';
	  wait for clk_period/2; 
end process;
                                        
END channel_monitor_arch;
