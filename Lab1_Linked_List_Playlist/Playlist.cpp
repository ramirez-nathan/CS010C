#include "Playlist.h"
#include <iostream>
#include <string>
using namespace std;

PlaylistNode::PlaylistNode() // default constructor (0 parameters) - initializes
                             // default values
    : uniqueID("none"), songName("none"), artistName("none"), songLength(0),
      nextNodePtr(nullptr) {}

PlaylistNode::PlaylistNode(
    const string &_uniqueID, const string &_songName, const string &_artistName,
    int _songLength) { // parameterized constructor (4 parameters) - initializes
                       // data memebers
  uniqueID = _uniqueID;
  songName = _songName;
  artistName = _artistName;
  songLength = _songLength;
  nextNodePtr = nullptr;
}
const string &PlaylistNode::GetID() const { return uniqueID; }
const string &PlaylistNode::GetSongName() const { return songName; }
const string &PlaylistNode::GetArtistName() const { return artistName; }
int PlaylistNode::GetSongLength() const { return songLength; }
PlaylistNode *PlaylistNode::GetNext() { return nextNodePtr; }
void PlaylistNode::InsertAfter(
    PlaylistNode *node) { // inputs a new song in the list
  node->nextNodePtr = this->nextNodePtr;
  this->nextNodePtr = node;
}
void PlaylistNode::SetNext(
    PlaylistNode *node) { // sets nextNodePtr to the next song
  nextNodePtr = node;
}

void PlaylistNode::PrintPlaylistNode() { // Prints data of each node
  cout << "Unique ID: " << uniqueID << endl;
  cout << "Song Name: " << songName << endl;
  cout << "Artist Name: " << artistName << endl;
  cout << "Song Length (in seconds): " << songLength << endl;
}

Playlist::Playlist() // (default constructor) - sets headNode and tailNode to
                     // nullptr
    : headNode(nullptr), tailNode(nullptr) 
    { 
    }

Playlist::~Playlist() { // destructor; deletes all the nodes in the linked list
  PlaylistNode *victim = headNode;
  while (victim != nullptr) {
    PlaylistNode *next = victim->GetNext();
    delete victim;
    victim = next;
  }
}
void Playlist::AddSong(const string &_ID, const string &_songName,
                       const string &_artistName, int _songLength) {
  PlaylistNode *newNode =
      new PlaylistNode(_ID, _songName, _artistName,
                       _songLength); // creates new node with those parameters
  if (headNode == nullptr) { // checks if list is empty; if empty then headNode
                             // and tailNode gets assigned to new node
    headNode = newNode;
    tailNode = newNode;
  } else { // if list is not empty, set tail to the new node
    tailNode->SetNext(newNode);
    tailNode = newNode;
  }
}
void Playlist::RemoveSong(
    const string &removeID) { // Remove function - takes the ID as a parameter
  PlaylistNode *prev = headNode;
  if (headNode == nullptr) { // checks if list is empty; if empty then nothing
                             // theres to remove
    return;
  } else {
    for (PlaylistNode *curr = headNode; curr != nullptr;
         curr = curr->GetNext()) { // transverse through list to check which
                                   // node has the wanted ID value
      if (removeID == curr->GetID()) {
        if (curr == headNode &&
            curr == tailNode) { // edge case: if the current node is the head &&
                                // tail, then delete node, set head and taill to
                                // null
          cout << '"' << curr->GetSongName() << '"' << " removed" << endl;
          delete curr;
          headNode = nullptr;
          tailNode = nullptr;
        } else if (headNode ==
                   curr) { // edge case: if the current node is head, set head
                           // to the next node, then delete current node
          headNode = curr->GetNext();
          cout << '"' << curr->GetSongName() << '"' << " removed" << endl;
          delete curr;
        } else if (tailNode ==
                   curr) { // edge case: if the current node is tail, set the
                           // previous node's next null
          prev->SetNext(nullptr);
          curr->SetNext(nullptr);
          tailNode = prev;
          cout << '"' << curr->GetSongName() << '"' << " removed" << endl;
          delete curr;
        } else { // last case: removing all other nodes
          prev->SetNext(curr->GetNext());
          curr->SetNext(nullptr);
          cout << '"' << curr->GetSongName() << '"' << " removed." << endl;
          delete curr;
        }
        return;
      }
      prev = curr; // assigns previous pointer to current pointer and continues
                   // to loop
    }
  }
}
void Playlist::OutputByArtist(
    const string
        &_artistName) { // function used to output songs by a specific artist
  PlaylistNode *curr = headNode;
  int counter = 1; // counter used to keep track of the number of songs
  while (curr != nullptr) {
    if (curr->GetArtistName() ==
        _artistName) { // if the current nodes' artist name is the same as the
                       // searched name, print current's PlaylistNode
      cout << counter << "." << endl;
      curr->PrintPlaylistNode();
      cout << endl;
    }
    counter = counter + 1;
    curr = curr->GetNext();
  }
}

void Playlist::ChangeSongPosition(
    int currPosition,
    int newPosition) { // function used to move a song's position
  PlaylistNode *prevNode = nullptr;
  PlaylistNode *currNode = headNode;
  int counter = 1;
  if (currPosition < 1) { // edge case: if the input current position is invalid
                          // (less than 1), then return
    cout << "Invalid position." << endl;
    return;
  }
  while (counter <
         currPosition) { // iterates through until the counter reaches the
                         // desired position the user wants to move the song to
    if (currNode != nullptr) {
      prevNode = currNode;
      currNode = currNode->GetNext();
      ++counter;
      if (currNode == nullptr) {
        cout << "Invalid position." << endl;
        return;
      }
    } else {
      cout << "Invalid position." << endl;
      return;
    }
  }
  string songName = currNode->GetSongName(); // gets name of the song of current
                                             // node for easier output
  if (prevNode == nullptr) {
    headNode = currNode->GetNext();
  } else {
    prevNode->SetNext(currNode->GetNext());
  }

  if (currNode->GetNext() == nullptr) {
    tailNode = prevNode;
  }

  if (newPosition <= 1) { // case: if the new position is less than 1, move node
                          // to the first position
    if (headNode == nullptr) {
      tailNode = currNode;
    }
    currNode->SetNext(headNode);
    headNode = currNode;
    cout << '"' << songName << '"' << " moved to position 1" << endl;
  } else { // once the wanted the position is found, this moves the node
    counter = 2;
    PlaylistNode *previousNode;
    PlaylistNode *nodeAfter;
    previousNode = headNode;
    nodeAfter = headNode->GetNext();

    while (counter < newPosition &&
           nodeAfter != nullptr) { // iterate through the linked list and move
                                   // the node to the correct position
      previousNode = nodeAfter;
      nodeAfter = nodeAfter->GetNext();
      ++counter;
    }
    previousNode->SetNext(currNode);
    currNode->SetNext(nodeAfter);
    if (!nodeAfter) {
      tailNode = currNode;
    }
    cout << '"' << songName << '"' << " moved to position " << counter << endl
         << endl;
  }
}

void Playlist::PrintPlaylist() const { // prints the whole playlist
  if (headNode == nullptr) {           // checks if list is empty
    cout << "Playlist is empty" << endl << endl;
    return;
  } else { // iterate through and output the node until curr is equal to null
    int counter = 1;
    PlaylistNode *curr = headNode;
    while (curr != nullptr) {
      cout << counter << "." << endl;
      curr->PrintPlaylistNode();
      cout << endl;
      curr = curr->GetNext();
      ++counter;
    }
  }
}

int Playlist::TotalPlaylistTime() const { // calculates total playlist time
  int sum = 0;
  PlaylistNode *current = headNode;
  while (current != nullptr) { // iterates through the linked list
    sum += current->GetSongLength();
    current = current->GetNext();
  }
  return sum;
}