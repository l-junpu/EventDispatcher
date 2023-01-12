#pragma once

#include "pch.h"

namespace jpd
{
	struct EventInterface
	{
		
	};

	template < typename... T_ARGS >
	struct Event : public EventInterface
	{
		struct Callback
		{
			using FnCallback = void(void*, T_ARGS&&...);

			FnCallback* m_Callback = nullptr;
			void*       m_Class    = nullptr;
		};
	};
	
	class EventDispatcher final
	{
	public:

		template < typename T_EVENT
				 , typename FUNCTION >
		void RegisterEvent(FUNCTION Func) noexcept
		{
			
		}

		template < typename T_EVENT
				 , typename T_CLASS
				 , typename FUNCTION >
		void RegisterEvent(T_CLASS& Class, FUNCTION Func) noexcept
		{
			
		}

		template < typename    T_EVENT
				 , typename... T_ARGS >
		void BroadcastEvent(T_ARGS&&... Args) noexcept
		{
			
		}

	private:

		std::unordered_map<std::uint64_t, EventInterface> m_EventsList;
	};
}