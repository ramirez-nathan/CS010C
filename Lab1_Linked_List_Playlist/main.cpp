#include "Playlist.h"
#include <iostream>
#include <string>
using namespace std;

void PrintMenu(string playlistTitle) {

  cout << playlistTitle << " PLAYLIST MENU" << endl;
  cout << "a - Add song" << endl;
  cout << "d - Remove song" << endl;
  cout << "c - Change position of song" << endl;
  cout << "s - Output songs by specific artist" << endl;
  cout << "t - Output total time of playlist (in seconds)" << endl;
  cout << "o - Output full playlist" << endl;
  cout << "q - Quit" << endl;
  cout << endl;
  cout << "Choose an option:" << endl;
}

int main() {
  string playlistTitle;
  char option; // User input for the menu
  Playlist uPlaylist;
  string uID;
  string unameOfSong;
  string unameOfArtist;
  int usongLength;
  int currPos;
  int newPos;
  string uartistOfChoice;

  cout << "Enter playlist's title:" << endl;
  cout << endl;
  getline(cin, playlistTitle);

  while (option != 'q') { // if user inputs q then program stops
    PrintMenu(playlistTitle);
    cin >> option;
    if (option == 'a') {
      cout << "ADD SONG" << endl;
      cout << "Enter song's unique ID:" << endl;
      cin >> uID;
      cin.ignore();
      cout << "Enter song's name:" << endl;
      getline(cin, unameOfSong);
      cout << "Enter artist's name:" << endl;
      getline(cin, unameOfArtist);
      cout << "Enter song's length (in seconds):" << endl;
      cin >> usongLength;
      // PlaylistNode* newSong = new PlaylistNode(ID, nameOfSong, nameOfArtist,
      // songLength);
      uPlaylist.AddSong(uID, unameOfSong, unameOfArtist, usongLength);
      cout << endl;
    } else if (option == 'd') {
      cout << "REMOVE SONG" << endl;
      cout << "Enter song's unique ID:" << endl;
      cin >> uID;
      cin.ignore();
      uPlaylist.RemoveSong(uID);
      cout << endl;
    } else if (option == 'c') {
      cout << "CHANGE POSITION OF SONG" << endl;
      cout << "Enter song's current position:" << endl;
      cin >> currPos;
      cout << "Enter new position for song:" << endl;
      cin >> newPos;
      uPlaylist.ChangeSongPosition(currPos, newPos);
    } else if (option == 's') {
      cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
      cout << "Enter artist's name:" << endl;
      cin.ignore();
      getline(cin, uartistOfChoice);
      cout << endl;
      uPlaylist.OutputByArtist(uartistOfChoice);
    } else if (option == 't') {
      cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
      cout << "Total time: " << uPlaylist.TotalPlaylistTime()
           << " seconds" << endl; // need to cout here because int function
      cout << endl;
    } else if (option == 'o') { // outputs full playlist from playlist.h file
      cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl;
      uPlaylist.PrintPlaylist();
    }
  }

  return 0;
}