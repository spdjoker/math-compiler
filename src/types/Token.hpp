#ifndef MATH_TOKEN_HPP
#define MATH_TOKEN_HPP

namespace compiler
{
	enum class Type {
		IDENTIFIER,
		FLOAT_LITERAL,
		OP_TERMINATOR,
		OP_ASSIGNMENT,
		OP_ADDITION,
		OP_SUBTRACTION,
		OP_MULTIPLICATION,
		OP_DIVISION,
		OP_MODULO,
		
		COUNT // LEAVE AS LAST
	};

	struct Token {
	private:
		Type m_type;
		void* m_value;
		int m_line;
		int m_column;

	public:
		Token(Type type, float value, int line, int columnStart) : 
			m_type(type), m_value(new float(value)), m_line(line), m_column(columnStart) {}
		Token(Type type, int value, int line, int columnStart) : 
			m_type(type), m_value(new int(value)), m_line(line), m_column(columnStart) {}
		Token(Type type, int line, int columnStart) : 
			m_type(type), m_value(nullptr), m_line(line), m_column(columnStart) {}
		
		float& asFloat() { return *((float*)m_value); }
		int& asInt() { return *((int*)m_value); }
		Type type() const { return m_type; }
		int line() const { return m_line; }
		int column() const { return m_column; }

		constexpr const char* typeName() const {
			switch (m_type) {
				case Type::IDENTIFIER:
					return "IDENTIFIER";

				case Type::FLOAT_LITERAL:
					return "FLOAT_LITERAL";

				case Type::OP_TERMINATOR:
					return "OP_TERMINATOR";
				case Type::OP_ASSIGNMENT:
					return "OP_ASSIGNMENT";
				case Type::OP_ADDITION:
					return "OP_ADDITION";
				case Type::OP_SUBTRACTION:
					return "OP_SUBTRACTION";
				case Type::OP_MULTIPLICATION:
					return "OP_MULTIPLICATION";
				case Type::OP_DIVISION:
					return "OP_DIVISION";
				case Type::OP_MODULO:
					return "OP_MODULO";

				default:
					return "UNKNOWN";
			}
		}

		bool isIdentifier() { return m_type == Type::IDENTIFIER; }
		bool isFloatLiteral() { return m_type == Type::FLOAT_LITERAL; }
		bool isStmtTerminator() { return m_type == Type::OP_TERMINATOR; }
		bool isOpAssign() { return m_type == Type::OP_ASSIGNMENT; }
	};
}
#endif
