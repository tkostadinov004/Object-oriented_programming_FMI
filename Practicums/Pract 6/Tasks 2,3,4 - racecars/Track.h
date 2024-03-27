#pragma once
class Track
{
	int slowCorners;
	int fastCorners;
	int straightLength;
public:
	Track();
	Track(int slowCorners, int fastCorners, int straightLength);
	int getSlowCorners() const;
	void setSlowCorners(int slowCorners);
	int getFastCorners() const;
	void setFastCorners(int fastCorners);
	int getStraightLength() const;
	void setStraightLength(int straightLength);
};