#pragma once
#include <vector>
class DynBitset {
public:

	void set(int i) {
		if (data.size() <= i) {
			data.resize(i + 1, false);
		}

		data[i] = true;
	}

	void reset(int i) {
		if (data.size() <= i) {
			data.resize(i + 1, false);
		}

		data[i] = false;
	}

	bool operator[](int i) {
		return data[i];
	};

	int size() {
		return data.size();
	}

	void clear() {
		data.clear();
	}


private:
	std::vector<bool> data;
};