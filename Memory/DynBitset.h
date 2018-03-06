#pragma once
#include <vector>
class DynBitset {
public:

	DynBitset() : data(0)
	{
	}

	void set(unsigned int i) {
		bool resized = false;
		if (data.size() <= i) {
			resized = true;
			data.resize(i + 1, false);
		}

		data.at(i) = true;
	}

	void reset(int i) {
		if (data.size() <= i) {
			data.resize(i + 1, false);
		}

		data[i] = false;
	}

	bool operator[](int i) {
		if (data.size() <= i) {
			data.resize(i + 1, false);
		}
		return data[i];
	};

	int size() const
	{
		return data.size();
	}

	void clear() {
		data.clear();
	}


private:
	std::vector<char> data;
};