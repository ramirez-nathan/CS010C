#include <iostream>
#include <string>
#ifndef PLAYLIST_H
#define PLAYLIST_H
using namespace std;

class PlaylistNode {
public:
  PlaylistNode();

  PlaylistNode(const string &_uniqueID, const string &_songName,
               const string &_artistName, int _songLength);

  const string &GetID() const;

  const string &GetSongName() const;

  const string &GetArtistName() const;

  int GetSongLength() const;

  PlaylistNode *GetNext();

  void InsertAfter(PlaylistNode *node);

  void SetNext(PlaylistNode *node);

  void PrintPlaylistNode();

private:
  string uniqueID;
  string songName;
  string artistName;
  int songLength;
  PlaylistNode *nextNodePtr;
};

class Playlist {
public:
  Playlist();

  ~Playlist();

  void AddSong(const string &ID, const string &songName,
               const string &artistName, int songLength);

  void RemoveSong(const string &removeID);

  void OutputByArtist(const string &_artistName);

  void PrintPlaylist() const;

  int TotalPlaylistTime() const;

  void ChangeSongPosition(int _curr, int _new);

private:
  PlaylistNode *headNode;
  PlaylistNode *tailNode;
  string name;
  Playlist(const Playlist &) = delete;
  Playlist & operator=(const Playlist &) = delete;
};
#endif
