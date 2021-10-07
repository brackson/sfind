# sfind Command

## Usage
    sfind -s [base_path] -n [search_string] -t [file_type]
    	-s OPTIONAL (default: ".")
    	-n REQUIRED only if file_type (-t) isn't given
    	-t OPTIONAL

## Summary
The sfind command is written in C and finds files and directories with names that include what the
[-n] flag specifies. By default, it starts searching in the current working
directory (.), but that can be changed with the -s argument, which is the base
path where we begin our recursive search.

The -t flag references the file type. When it's unspecified, it does not bother
to look at a file types. Only one file type can be used in the search. The
following file types are permitted:

	f	regular file
	d	directory
	c	character device file
	b	block device file
	l	symbolic link
	p	named pipe
	s	local socket file

The -n (search string) flag is required, unless you're using the -t (file type)
flag. When you use the `sfind` command and specify a file type without specifying
a search string, it will recursively search directories for any file type that
matches.

## Original Project Overview

You will implement a simplified version of the UNIX command find, here called:
sfind that recursively searches directories for files or directories that match
a substring given on the command line.

The syntax of your command should look like this:

`sfind <directory-where to start looking> -n substring-criteria -t <filetype> `

As background what you (really) are implementing is the UNIX equivalent of:

`find <directory-where to start looking> -name substring -print -type <filetype>`

Here are some example uses:

 - `$ sfind ~maria -n exam-solutions.txt`
    - The above command line should find all the files and directories
    containing the string "exam-solutions.txt" starting from the directory
    ~maria OR in any of the subdirectories that descends from the ~maria.
    The files returned can be of any type since it is not defined by the -t flat.
 - `$ sfind . -n .txt -t f`
   - The above command line should find all the files and directories containing the string ".txt" in the current directory OR in any of the subdirectories that descends from the current directory. The files returned must be 'regular files' (the file types shold be at the same syntax as specified by the find command and to query the type you should use `lstat()`.
 - `$ sfind . -n maria`
    - The above command line is similar to the first example, except that it starts searching from
the current directory, and searches for the substring 'maria'.
