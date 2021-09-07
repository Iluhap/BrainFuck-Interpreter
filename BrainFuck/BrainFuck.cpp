#include "BrainFuck.h"

namespace BrainFuck
{
	// ---------- Class methods ---------- //
	Interpreter::Interpreter(std::string code)
	{
		m_str.resize(30000);
		m_str_iter = m_str.begin();

		TranslateCommands(code);
		m_procedure_iter = m_procedures.begin();
	}

	void Interpreter::ExecuteProgram()
	{
		while (m_procedure_iter != m_procedures.end())
		{
			(*(*m_procedure_iter)).Action(m_str_iter, m_procedure_iter);
			m_procedure_iter++;
		}
	}

	std::string Interpreter::GetOutput()
	{
		return m_str;
	}

	void Interpreter::TranslateCommands(std::string commands)
	{
		for (char command : commands) // Interpreting commands into procedure objects
		{
			ProcedureID id = GetCommandID(command);

			if (id != ProcedureID::None)
			{
				m_procedures.push_back(
					std::unique_ptr<Procedure>(CreateProcedure(id))
				);
			}
		}
	}

	Interpreter::ProcedureID Interpreter::GetCommandID(char command)
	{
		switch (command)
		{
		case '>':
			return ProcedureID::RightArrow;
		case '<':
			return ProcedureID::LeftArrow;
		case '+':
			return ProcedureID::Plus;
		case '-':
			return ProcedureID::Minus;
		case '[':
			return ProcedureID::OpenBracket;
		case ']':
			return ProcedureID::CloseBracket;
		case '.':
			return ProcedureID::Dot;
		default:
			return ProcedureID::None;
		}
	}

	Interpreter::Procedure* Interpreter::CreateProcedure(ProcedureID id)
	{
		switch (id)
		{
		case ProcedureID::RightArrow:
			return new RightArrow;

		case ProcedureID::LeftArrow:
			return new LeftArrow;

		case ProcedureID::Plus:
			return new Plus;

		case ProcedureID::Minus:
			return new Minus;

		case ProcedureID::OpenBracket:
			return new OpenBracket;

		case ProcedureID::CloseBracket:
			return new CloseBracket;

		case ProcedureID::Dot:
			return new Dot;

		case ProcedureID::None:
			return nullptr;
		}
	}
}

namespace BrainFuck // Implementation of Procedure subclasses
{
	void Interpreter::RightArrow::Action(strIter& str_iter, vectIter& procedure_iter)
	{
		str_iter++;
	}

	void Interpreter::LeftArrow::Action(strIter& str_iter, vectIter& procedure_iter)
	{
		str_iter--;
	}

	void Interpreter::Plus::Action(strIter& str_iter, vectIter& procedure_iter)
	{
		(*str_iter)++;
	}

	void Interpreter::Minus::Action(strIter& str_iter, vectIter& procedure_iter)
	{
		(*str_iter)--;
	}

	void Interpreter::OpenBracket::Action(strIter& str_iter, vectIter& procedure_iter)
	{
		if (!(*str_iter))
		{
			ProcedureID cur_id = ProcedureID::None;
			do
			{
				procedure_iter++;
				cur_id = (*(*procedure_iter)).GetID();
			} while (cur_id != ProcedureID::CloseBracket);
		}
	}

	void Interpreter::CloseBracket::Action(strIter& str_iter, vectIter& procedure_iter)
	{
		ProcedureID cur_id = ProcedureID::None;
		do
		{
			procedure_iter--;
			cur_id = (*(*procedure_iter)).GetID();
		} while (cur_id != ProcedureID::OpenBracket);

		procedure_iter--;
	}

	void Interpreter::Dot::Action(strIter& str_iter, vectIter& procedure_iter)
	{
		std::cout << *str_iter;
	}
}