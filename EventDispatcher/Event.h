#pragma once

namespace jpd
{
	struct EventInterface
	{
		virtual ~EventInterface(void) noexcept = default;
	};

	template < typename... T_ARGS >
	struct EventGroup : public EventInterface
	{
		struct Callback
		{
			using FnDetails = void(void*, T_ARGS&&...);

			FnDetails*  m_Callback = nullptr;
			void*       m_Class    = nullptr;
		};
		using EventsList = std::vector<EventInterface>;

		EventGroup(void) noexcept = default;
		virtual ~EventGroup(void) noexcept = default;

		template < typename FUNCTION >
		void InsertEvent(FUNCTION&& Func, T_ARGS&&... Args) noexcept
		{
			m_List.push_back(
				Callback
				{
					.m_pCallback = [](void* Class, T_ARGS&&...)
						 		   {
									   std::invoke( Func
												  , std::forward<T_ARGS&&>(Args)... );
								   }
				,	.m_pClass = nullptr
				});
		}

		template < class    T_CLASS
				 , typename FUNCTION >
		void InsertEvent(T_CLASS* Class, FUNCTION&& Func, T_ARGS&&... Args) noexcept
		{
			m_List.push_back(
				Callback
				{
					.m_pCallback = [](void* pClass, T_ARGS&&...)
								   {
									   std::invoke( Func
												  , reinterpret_cast<T_CLASS*>(pClass)
									              , std::forward<T_ARGS&&>(Args)... );
								   }
				,	.m_pClass = Class
				});
		}


		EventsList m_List;
	};
}


#define CREATE_EVENT(Name, ...)						    	\
	struct Name : public jpd::EventGroup<__VA_ARGS__>       \
	{									                    \
		static constexpr auto name_v = #Name;		        \
	};