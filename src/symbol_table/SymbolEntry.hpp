#ifndef MATH_SYMBOL_ENTRY_HPP
#define MATH_SYMBOL_ENTRY_HPP 

#include <string>

namespace compiler
{
	struct SymbolEntry {
		struct Data {
			float value;
			const std::string name;
			const int id;
			bool init;

			Data(const std::string& key, int id) : name(key), value(0.0f), id(id) {} 
		};

		SymbolEntry(Data* data, bool success) : m_data(data), m_success(success) {} 
		SymbolEntry() : m_data(nullptr), m_success(false) {} 

		Data& data() { return *m_data; }
		bool success() const { return m_success; }
		bool exists() const { return m_data; }

	private: 
		Data* m_data; 
		bool m_success;
	};
}

#endif
