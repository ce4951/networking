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
-- Generated on "09/25/2018 20:52:30"
                                                            
-- Vhdl Test Bench template for design  :  timer
-- 
-- Simulation tool : ModelSim-Altera (VHDL)
-- 

LIBRARY ieee;                                               
USE ieee.std_logic_1164.all;                                

ENTITY tb_timer IS
END tb_timer;
ARCHITECTURE timer_arch OF tb_timer IS
-- constants                                                 
-- signals                                                   
SIGNAL clk : STD_LOGIC := '0';
SIGNAL interrupt_n : STD_LOGIC;
SIGNAL rst_n : STD_LOGIC := '1';
COMPONENT timer
	PORT (
	clk : IN STD_LOGIC;
	interrupt_n : BUFFER STD_LOGIC;
	rst_n : IN STD_LOGIC
	);
END COMPONENT;
BEGIN
	i1 : timer
	PORT MAP (
-- list connections between master ports and signals
	clk => clk,
	interrupt_n => interrupt_n,
	rst_n => rst_n
	);

	clk_process : process
   begin
        clk <= '0';
        wait for 10 ns;
        clk <= '1';
        wait for 10 ns;
   end process;
	
	simProcess : process
	begin
		wait for 150 ms;
		rst_n <= '0';
		wait for 10 ms;
		rst_n <= '1';
	end process;
	
                                         
END timer_arch;
