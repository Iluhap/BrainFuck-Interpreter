#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace BrainFuck
{
	/*
	* Main class used to create object that receive BrainFuck code as parameter
	* interpret code into procedure model 
	* and execute it   
	*/
	class Interpreter
	{
	public: // Class interface

		Interpreter(std::string code);

		void ExecuteProgram();

	private:

		/*
		* Class used to identify procedures
		*/
		enum class ProcedureID
		{
			None,
			RightArrow, LeftArrow,
			Plus, Minus,
			OpenBracket, CloseBracket,
			Dot
		};

		/*
		* Class represents interface of model items 
		*/
		class Procedure;

		typedef std::unique_ptr<Procedure> pProcedure;
		typedef std::vector<pProcedure>::iterator vectIter;
		typedef std::string::iterator strIter;

	private: // Helper methods

		Interpreter();

		void TranslateCommands(std::string commands);

		ProcedureID GetCommandID(char command);

		Procedure* CreateProcedure(ProcedureID id);

	private: // Data members

		std::string m_str;
		strIter m_str_iter;

		std::vector<pProcedure> m_procedures;
		vectIter m_procedure_iter;

	private: // Procedure subclasses announcement

		class RightArrow;
		class LeftArrow;
		class Plus;
		class Minus;
		class OpenBracket;
		class CloseBracket;
		class Dot;

	};


	class Interpreter::Procedure
	{
	public:
		virtual void Action(strIter&, vectIter&) = 0;
		virtual ProcedureID GetID() { return ProcedureID::None; }
	};

	// ---------- Declaration of internal Procedure subclasses ---------- //

	class Interpreter::RightArrow : public Procedure
	{
	public:
		void Action(strIter&, vectIter&) override;
		ProcedureID GetID() { return ProcedureID::RightArrow; }
	};

	class Interpreter::LeftArrow : public Procedure
	{
	public:
		void Action(strIter&, vectIter&) override;
		ProcedureID GetID() { return ProcedureID::LeftArrow; }
	};

	class Interpreter::Plus : public Procedure
	{
	public:
		void Action(strIter&, vectIter&) override;
		ProcedureID GetID() { return ProcedureID::Plus; }
	};

	class Interpreter::Minus : public Procedure
	{
	public:
		void Action(strIter&, vectIter&) override;
		ProcedureID GetID() { return ProcedureID::Minus; }
	};

	class Interpreter::OpenBracket : public Procedure
	{
	public:
		void Action(strIter&, vectIter&) override;
		ProcedureID GetID() { return ProcedureID::OpenBracket; }
	};

	class Interpreter::CloseBracket : public Procedure
	{
	public:
		void Action(strIter&, vectIter&) override;
		ProcedureID GetID() { return ProcedureID::CloseBracket; }
	};

	class Interpreter::Dot : public Procedure
	{
	public:
		void Action(strIter&, vectIter&) override;
		ProcedureID GetID() { return ProcedureID::Dot; }
	};
}