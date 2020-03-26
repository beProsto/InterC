#ifndef INTERC_IMAP_HPP_HEADER_FILE_GUARD
#define INTERC_IMAP_HPP_HEADER_FILE_GUARD

namespace InterC {
template<typename T, typename Y> class IMap {
public:	
	IMap() {

	}
	~IMap() {

	}

	Y& operator[](const T& _key) {
		for(std::pair<T, Y>& p : m_Data) {
			if(p.first == _key) {
				return p.second;			
			}
		}

		m_Data.push_back(std::pair<T, Y>());
		m_Data[m_Data.size() - 1].first = _key;
		return m_Data[m_Data.size() - 1].second;
	}

	std::pair<T, Y>* BeginPtr() {
		return &*m_Data.begin();
	}
	std::pair<T, Y>* EndPtr() {
		return &*m_Data.end();
	}
	std::pair<T, Y>* Find(const T& _key) {
		for(std::pair<T, Y>& p : m_Data) {
			if(p.first == _key) {
				return &p;			
			}
		}

		return EndPtr();
	}

	void Erase(std::pair<T, Y>* _where, std::pair<T, Y>* _toWhere) {
		size_t s1 = std::distance(_where, BeginPtr());
		size_t s2 = std::distance(_toWhere, BeginPtr());
		m_Data.erase(m_Data.begin() + s1, m_Data.begin() + s2);
	}
	void Erase(std::pair<T, Y>* _where) {
		size_t s1 = std::distance(_where, BeginPtr());
		m_Data.erase(m_Data.begin() + s1);
	}

private:
	std::vector<std::pair<T, Y>> m_Data;
};
}

#endif/*INTERC_IMAP_HPP_HEADER_FILE_GUARD*/
