#ifndef CARD_H
#define CARD_H

struct RotatedCard{
	RotatedCard(char t, char r, char b, char l) :
		top(t), right(r), bottom(b), left(l)
	{}

	char top;
	char right;
	char bottom;
	char left;
};

class Card{
public:
	Card(char t, char r, char b, char l) :
		rot_{RotatedCard(t,r,b,l),
			 RotatedCard(l,t,r,b),
			 RotatedCard(b,l,t,r),
			 RotatedCard(r,b,l,t)}
	{}

	const RotatedCard& rot(int index) const {
		return rot_[index];
	}

private:
	RotatedCard rot_[4];
};

// compare two std::vector<int>
inline bool vector_equals(const std::vector<int>& a, const std::vector<int>& b) {
	if (a.size() != b.size()) {
		return false;
	}
	for (unsigned int i = 0; i < a.size(); ++i) {
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;
}

// add rotation to every entry (modulo 4)
inline std::vector<int> rotate_vector(const std::vector<int>& v, int rotate_by) {
	std::vector<int> result;
	for (const auto& value : v) {
		result.push_back((value+rotate_by)%4);
	}
	return result;
}


// print std::vector<int>
inline std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
	os << "[";
	for (unsigned int i = 0; i < v.size() - 1; ++i) {
		os << v[i] << ", ";
	}
	if (!v.empty()) {
		os << v.back();
	}
	os << "]";
	return os;
}

struct Solution{
	Solution() = default;
	Solution(char a_, char rot_a_, char b_, char rot_b_, char c_, char rot_c_,
			 char d_, char rot_d_, char e_, char rot_e_, char f_, char rot_f_,
			 char g_, char rot_g_, char h_, char rot_h_, char i_, char rot_i_) :
				 a(a_), rot_a(rot_a_), b(b_), rot_b(rot_b_), c(c_), rot_c(rot_c_),
				 d(d_), rot_d(rot_d_), e(e_), rot_e(rot_e_), f(f_), rot_f(rot_f_),
				 g(g_), rot_g(rot_g_), h(h_), rot_h(rot_h_), i(i_), rot_i(rot_i_)
	{}

	char a,rot_a, b,rot_b, c,rot_c;
	char d,rot_d, e,rot_e, f,rot_f;
	char g,rot_g, h,rot_h, i,rot_i;

	// a  b  c
	// d  e  f
	// g  h  i

	// the outer cards a,b,c,f,i,h,g,d (first row/column given by start_index)
	std::vector<int> get_frame(int start_index) const {
		std::vector<int> r(8,0);
		switch(start_index) {
			case 0: r[0] = a; r[1] = b; r[2] = c; r[3] = f; r[4] = i; r[5] = h; r[6] = g; r[7] = d; break;
			case 1: r[0] = c; r[1] = f; r[2] = i; r[3] = h; r[4] = g; r[5] = d; r[6] = a; r[7] = b; break;
			case 2: r[0] = i; r[1] = h; r[2] = g; r[3] = d; r[4] = a; r[5] = b; r[6] = c; r[7] = f; break;
			case 3: r[0] = g; r[1] = d; r[2] = a; r[3] = b; r[4] = c; r[5] = f; r[6] = i; r[7] = h; break;
		}
		return r;
	}

	// rotation of the outer cards a,b,c,f,i,h,g,d (first row/column given by start_index)
	std::vector<int> get_frame_rotations(int start_index) const {
		std::vector<int> r(8,0);
		switch(start_index) {
			case 0: r[0] = rot_a; r[1] = rot_b; r[2] = rot_c; r[3] = rot_f; r[4] = rot_i; r[5] = rot_h; r[6] = rot_g; r[7] = rot_d; break;
			case 1: r[0] = rot_c; r[1] = rot_f; r[2] = rot_i; r[3] = rot_h; r[4] = rot_g; r[5] = rot_d; r[6] = rot_a; r[7] = rot_b; break;
			case 2: r[0] = rot_i; r[1] = rot_h; r[2] = rot_g; r[3] = rot_d; r[4] = rot_a; r[5] = rot_b; r[6] = rot_c; r[7] = rot_f; break;
			case 3: r[0] = rot_g; r[1] = rot_d; r[2] = rot_a; r[3] = rot_b; r[4] = rot_c; r[5] = rot_f; r[6] = rot_i; r[7] = rot_h; break;
		}
		return r;
	}

	// same center card and "same" frame (only rotated)
	// also: correct rotations
	bool is_same_as(const Solution& s) const {
		if (e != s.e) { // same center card?
			return false;
		}
		std::vector<int> my_frame = get_frame(0);
		for (int i = 0; i < 4; ++i) {
			if (vector_equals(my_frame, s.get_frame(i))) { // same frame? (possibly rotated)
				// correct rotations?
				if (((rot_e+i)%4 == s.rot_e) && vector_equals(rotate_vector(get_frame_rotations(0),i), s.get_frame_rotations(i))) {
					return true;
				}
			}
		}
		return false;
	}

/*
	std::vector<int> get_line(int index) {
		std::vector<int> result(3,0);
		switch(index) {
			case 0:	result[0] = a; result[1] = b; result[2] = c; break;
			case 1: result[0] = c; result[1] = f; result[2] = i; break;
			case 2: result[0] = i; result[1] = h; result[2] = g; break;
			case 3: result[0] = g; result[1] = d; result[2] = a; break;
		}
		return result;
	}

	std::vector<int> get_frame(int start_index) {
		std::vector<int> result = get_line(start_index);
		std::vector<int> temp;
		for (int i = 1; i <= 3; ++i) {
			temp = get_line((start_index + i)%4);
			result.insert(result.end(),temp.begin()+1,temp.end());
		}
		return result;
	}
*/

};

// print rotated card
inline std::ostream& operator<<(std::ostream& os, const RotatedCard& rc) {
	os << "[" << (int)rc.top << "," << (int)rc.right << "," << (int)rc.bottom << "," << (int)rc.left << "]";
	return os;
}

// print card, represented by its 0 rotation
inline std::ostream& operator<<(std::ostream& os, const Card& c) {
	os << c.rot(0);
	return os;
}

// print solution
inline std::ostream& operator<<(std::ostream& os, const Solution& s) {
	os << (int)s.a << "_" << (int)s.rot_a << "\t\t" << (int)s.b << "_" << (int)s.rot_b << "\t\t" << (int)s.c << "_" << (int)s.rot_c << "\n"
	   << (int)s.d << "_" << (int)s.rot_d << "\t\t" << (int)s.e << "_" << (int)s.rot_e << "\t\t" << (int)s.f << "_" << (int)s.rot_f << "\n"
	   << (int)s.g << "_" << (int)s.rot_g << "\t\t" << (int)s.h << "_" << (int)s.rot_h << "\t\t" << (int)s.i << "_" << (int)s.rot_i << "\n";
	return os;
}

#endif
