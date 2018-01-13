# Dotify
Brian Hao


A console app that allows a user to maintain a library of songs and create and manage playlists containing said songs.

### Commands available to the user
The following are the actions available to the user when using Dotify:

##### AS
This command adds a new song to the user’s library. The user specifies the song’s name, artist, 
and album. By default, the song is assigned the next available identifier and starts with 0 plays. 
If the song already exists in the library, indicate the problem.


##### RS
This command removes a song from the user’s library and any playlists that that song belongs to. 
The user specifies the song’s identifier. Display the playlists that the song was removed from. 
If the song does not exist in the library, indicate the problem.


##### PLY
This command plays a song in the user’s library a certain number of times. The user specifies the 
song’s identifier and the number of times to play the song. If the provided value is invalid, assume 
that the song was played 0 times. Display the number of plays started with and the new number of plays 
for that song. If the song does not exist in the library, indicate the problem.


##### LB
This command displays all of the songs in the user’s library. The user specifies the criterion to order 
the songs by—name, artist, album, or plays. The songs are displayed in a numbered list, with each displaying 
its name, artist, album, plays, and identifier.


#### AP
This command creates a new playlist. The user specifies the playlist’s title. By default, the playlist 
starts off with a rating of 1 and no songs. The app must not contain duplicate playlists (i.e., playlists 
with the same title). If the playlist already exists, indicate the problem.


#### RP
This command removes a playlist. The user specifies the playlist’s title. If the playlist does not exist, 
indicate the problem.


#### RN
This command renames an existing playlist. The user specifies the current title of the playlist to change 
and the new title. If the playlist does not exist or if a playlist with the specified title already exists, 
indicate the problem.


#### ASP
This command adds a song from the user’s library to an existing playlist. The user specifies the playlist to 
add to and the song to be added. If the playlist does not exist, if the song does not exist in the library, 
or if the song being added already exists in the playlist, indicate the problem.


#### RSP
This command removes a song from a playlist. The user specifies the playlist to remove the song from and the 
song to be removed. If the playlist does not exist or if the song does not exist in the playlist, indicate 
the problem.


#### RT
This command gives a new rating to a playlist. The user specifies the playlist to rate and a rating from 1 to 5. 
If the playlist does not exist, if the song does not exist in the playlist, or if the rating is invalid, indicate 
the problem.


#### PL
This command displays all of the songs in a playlist. The user specifies the playlist. The songs are displayed 
in a numbered list in the order that they were added to the playlist, and each song shows its name, artist, album, 
number of plays, and identifier.


#### PLS
This command displays all of the playlists. The playlists are displayed in a numbered list ordered first by rating 
and then alphabetically by title. Each playlist shows its title, rating, and number of songs.


#### EXP
This command exports the song library and playlists to files. The songs in the library will be exported to their own 
file and the playlists will be exported to their own file, based on the file format specified earlier. The user specifies 
the name of the library file and the name of the playlists file. If a file with a provided name already exists, then 
overwrite it. If the library contains no songs or if there are no playlists, then simply generate empty files.


#### HELP
This command displays all of the available commands and their descriptions.




### Export File Format

A library data file contains all of the library’s songs—one song on every line. Each individual component of a song’s 
data is separated by a pipe character (“|”) and is ordered as follows—name, artist, album, number of plays, and 
identifier. For example:

`Dreaming of A Red Christmas|DJT|Take Over|2|18`

`Election Blues|The Dems|2016|107|39`

`War and Peace|The Confused|Super Confused|18|45`

`How?|The Confused|Very Very Confused|9|20`

`WHO DID IT|The Dems|2016|0|93`


A playlist data file contains all of the playlists. The first line of a “playlist” contains a pipe character separated 
grouping of the title, the rating, and the number of songs in the playlist. Each subsequent line contains a pipe character 
separated grouping of a song’s name, artist, and album.

`The Sadz|2|5`

`Dreaming of A Red Christmas|DJT|Take Over`

`Election Blues|The Dems|2016`

`War and Peace|The Confused|Super Confused`

`How?|The Confused|Very Very Confused`

`WHO DID IT|The Dems|2016`

`Happy Songs|5|1`

`Apples are a Way of Life|The Simons|The Fruit Album`


## Compilation Instructions
Compile your code with:

`$ make`

Execute using:

`./Dotify`

Alternatively, you may load a library (and optionally, a playlist) file by using:

`./Dotify <library file name> <playlists file name>`
