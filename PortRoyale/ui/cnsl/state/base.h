#ifndef UI_CNSL_STATE_BASE_HEADER_INCLUDED
#define UI_CNSL_STATE_BASE_HEADER_INCLUDED

#include "registrar.hpp"

namespace ui
{
	namespace cnsl
	{
		class CommandDescription;

		namespace state
		{
			class Context;

			class BaseInterface
			{
			protected:
				Context& context;

			public:
				BaseInterface(Context& context) noexcept;
				virtual ~BaseInterface() noexcept = 0;

				virtual BaseInterface* Clone() const = 0;

				virtual void Initialize() = 0;
				virtual void Terminate() = 0;

				virtual void DrawConsole() const = 0;
				virtual void GetAvailableCommands(CommandDescription*& commandDescriptionBuffer) const = 0;
			};

			template<typename Derived>
			class Base :
				public BaseInterface
			{
			private:
				static const Registrar<Derived> registrar;

			public:
				using BaseInterface::BaseInterface;
				virtual ~Base() noexcept {};

				virtual BaseInterface* Clone() const override
				{
					static const int dummy = registrar.Dummy();

					return static_cast<BaseInterface*>(new Derived(static_cast<const Derived&>(*this)));
				}
			};

			template<typename Derived>
			const Registrar<Derived> Base<Derived>::registrar(Derived::TYPE);
		}
	}
}

#endif