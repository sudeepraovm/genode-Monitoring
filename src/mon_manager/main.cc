/* global includes */
#include <base/env.h>
#include <base/printf.h>
#include <base/rpc_server.h>
#include <base/sleep.h>
#include <cap_session/connection.h>
#include <root/component.h>

#include "mon_manager/mon_manager.h"

/* local includes */
#include "mon_manager/mon_manager_session.h"

namespace Mon_manager
{

	struct Session_component : Genode::Rpc_object<Session>
	{

		private:

			Mon_manager *_monmanager = nullptr;

		public:
			enum { CAP_QUOTA = 2 };
			Genode::size_t update_info(Genode::Dataspace_capability ds_cap)
			{
				return _monmanager->update_info(ds_cap);
			}

			void update_rqs(Genode::Dataspace_capability ds_cap)
			{
				_monmanager->update_rqs(ds_cap);
			}

			void update_dead(Genode::Dataspace_capability ds_cap)
			{
				_monmanager->update_dead(ds_cap);
			}

			int get_num_cores()
			{
				return _monmanager->get_num_cores();
			}

			Genode::Trace::Execution_time get_idle_time(int core)
			{
				return _monmanager->get_idle_time(core);
			}

			bool is_core_online(int core)
			{
				return _monmanager->is_core_online(core);
			}

			int get_util(int core)
			{
				return _monmanager->get_util(core);
			}

			Session_component(Mon_manager *monmanager)
			: Genode::Rpc_object<Session>()
			{
				_monmanager = monmanager;
			}

	};

	class Root_component : public Genode::Root_component<Session_component>
	{

		private:

			Mon_manager *_monmanager = nullptr;

		protected:

			Session_component *_create_session(const char *args)
			{
				return new (md_alloc()) Session_component(_monmanager);
			}

		public:

			Root_component(Genode::Rpc_entrypoint *ep,
			               Genode::Allocator *allocator,
			               Mon_manager *monmanager)
			: Genode::Root_component<Session_component>(ep, allocator)
			{
				_monmanager = monmanager;
			}
	};

}

using namespace Genode;

int main()
{
	Mon_manager::Mon_manager monmanager;

	Cap_connection cap;

	static Sliced_heap sliced_heap(env()->ram_session(),
	                               env()->rm_session());

	enum { STACK_SIZE = 4096 };
	static Rpc_entrypoint ep(&cap, STACK_SIZE, "mon_manager_ep");

	static Mon_manager::Root_component mon_manager_root(&ep, &sliced_heap, &monmanager);
	env()->parent()->announce(ep.manage(&mon_manager_root)); 

	sleep_forever();

	return 0;
}
