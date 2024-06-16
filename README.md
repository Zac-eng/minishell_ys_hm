# minishell_ys_hm
Minishell 42.

# Explanation of how functions works on bash
- echo
- echo with option -n
-  cd with only a relative or absolute path
-  pwd with no options
-  export with no options
-  unset with no options
-  env with no options or arguments
-  exit with no options

# Make Options
- make
	-	compile all files required and create executable, "minishell"
- make clean
	-	removes unnecessary *.o files not necessary to run program
- make fclean
	-	removes everything created by make, including "minishell"
- make re
	-	removes everything and compile again.

# general knowledge
- PATH_MAX
	-	in Mac in 42 Tokyo (Mac OS Mojave), the maximum length of a file or directory is 255, and the total pathline should be less than 1024.(PATH_MAX)
- status number
	-	command not found: 127
	-	parse error: 258
	-	failed to execute command: 1
