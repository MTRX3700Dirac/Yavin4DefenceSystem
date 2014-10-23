Yavin4DefenceSystem
===================

Instructions for using Git
--------------------------

Please try and submit raw files as much as possible and not zips, it makes it a hassle to edit
---------------------------------------------------------------------------------------------
Note: depending on user account permissions, sudo may be required on linux

DO NOT CREATE A LOCAL BRANCH TO WORK ON FOR A WEEK AND THEN TRY TO SIMPLY MERGE IT WITH THE MASTER
yesterday we lost almost a weeks worth of work, and have spent many hours trying to get everything 
working again because people merged an old version and deleted a whole lot of stuff

-**1)**
Clone into the repository so you keep a [you guessed it] clone of the repo on
local filesystem:

git clone https://github.com/MTRX3700Dirac/Yavin4DefenceSystem [Source-Directory]                                                                                         

After this, issue commands from within the source-directory   

-**1b)**
If using SourceTree, make a new branch so all your changes are put in its own branch. A branch 
is like an online copy of your local changes, and should hold the code you are working on before
they it is integrated into the master.                                                                                                       

-**2)**
Make a change to a file in the repo, and commit the change, like this readme

git commit README.md                                                                                                                                                      

This saves changes LOCALLY. For committing changes to the online repo,

git push https://github.com/MTRX3700Dirac/Yavin4DefenceSystem

or just

git push

-**3)**
To refresh your local repo copy to the latest, use

git pull

or for a specific folder in the repo,

git pull https://github.com/MTRX3700Dirac/Yavin4DefenceSystem/FOLDER


**For all other git needs**
http://stackoverflow.com/questions/315911/git-for-beginners-the-definitive-practical-guide/

SIGNED:
Bas Uytterhoeven-Spark
Jacob Mackay

