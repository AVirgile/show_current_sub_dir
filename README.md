# show_current_sub_dir

This is a CLI program to show all the sub directories and their content from the current directory

## How to install

```
$> git clone 
$> cd setup_scripts
$> ./install.sh
```
restart your terminal after installation

## How to run

type in your terminal the following command the command have a set of flags that have an impact
on the output of the command

```
$> scsd [potential flags] ...
```
### all the flags currently implemented

-a : show all hiden directories except for '..'
-d : show only the directories
-s : show the size of the different files and directories
-f : show the fullpath instead of the name of the different files and directories
-D : show the date of the last modification of the different files and directories
-t : sort the file from the last modified file to the more recent modify file

this flags can be combine together to achieve a more detail output

## How to uninstall

```
$> cd setup_scripts
$> ./delete.sh
```
