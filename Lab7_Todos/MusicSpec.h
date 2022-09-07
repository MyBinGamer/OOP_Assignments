#pragma once
#include "ItemSpec.h"
#include <string>
#include <cstring>

using namespace std;
class MusicSpec : public ItemSpec
{
public:
	enum class Genre { ANY, EDM, ROCK, JAZZ, DUBSTEP, TECHNO, ELECTRO };
	MusicSpec() = default;
	MusicSpec(string artist, string album, int year, Genre genre)
		: _artist{ artist }, _album{ album }, _year{year}, _genre{ genre } {}

	Genre get_genre() const { return _genre; }
	string get_artist() const { return _artist; }
	string get_album() const { return _album; }
	int get_year() const { return _year; }
	bool matches(const ItemSpec& otherSpec) const override;

	void send_to(ostream& os) const override;

private:
	string _artist;
	string _album;
	int _year;
	Genre _genre;
};

