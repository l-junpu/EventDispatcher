#pragma once

#include "Event.h"
#include "pch.h"

namespace jpd
{
	class EventDispatcher final
	{
	public:

		template < typename T_EVENT
				 , typename FUNCTION >
		void RegisterEvent(FUNCTION&& Func) noexcept
		{
			RegisterEvent_IfNeeded<T_EVENT>( std::forward<FUNCTION&&>(Func) );

			//static_cast<T_EVENT*>(EventGrp)->InsertEvent(std::forward<FUNCTION&&>(Func));
		}

		template < typename T_EVENT
				 , class    T_CLASS
				 , typename FUNCTION >
		void RegisterEvent(T_CLASS* Class, FUNCTION&& Func) noexcept
		{
			//auto [Uid, EventGrp] = *(RegisterEvent_IfNeeded<T_EVENT>( std::forward<FUNCTION&&>(Func) ));

			//static_cast<T_EVENT*>(EventGrp)->InsertEvent( Class
			//	                                        , std::forward<FUNCTION&&>(Func) );
	 	}

		template < typename    T_EVENT
				 , typename... T_ARGS >
		void BroadcastEvent(T_ARGS&&... Args) noexcept
		{
			
		}

	private:

		template < typename T_EVENT
				 , typename FUNCTION >
		std::unordered_map<std::uint64_t, EventInterface*>::iterator RegisterEvent_IfNeeded(FUNCTION&& Func) noexcept
		{
			std::unordered_map<std::uint64_t, EventInterface*>::iterator ReturnIt;

			// Generate Hash ID - Using Event Name & Function Signature
			auto Name = std::string(T_EVENT::name_v) + typeid(Func).name();
			auto Hash = xxh::xxhash<64>(Name);

			// Emplace New Event (If Needed)
			auto QueryEvent = m_EventsMap.find(Hash);

			if (QueryEvent == m_EventsMap.end())
			{
				// On Emplace, Assign Event As New Iterator
				m_EventsList.push_back(std::make_unique<T_EVENT>());
				ReturnIt = m_EventsMap.emplace(Hash, *(m_EventsList.back())).first;
			}
			
			return ReturnIt;
		}

		std::vector<std::unique_ptr<EventInterface>>       m_EventsList;
		std::unordered_map<std::uint64_t, EventInterface*> m_EventsMap;
	};
}