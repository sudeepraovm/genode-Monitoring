#pragma once

#include <base/signal.h>
#include <mon_manager/mon_manager_session.h>
#include <os/attached_ram_dataspace.h>
#include <os/server.h>
#include <root/component.h>
#include <timer_session/connection.h>
#include <util/string.h>
#include <cap_session/connection.h>
#include <trace_session/connection.h>
namespace Mon_manager{
struct Monitoring_object
{
	Genode::Trace::Session_label      session_label;
	Genode::Trace::Thread_name        thread_name;
	Genode::Trace::Policy_id          policy_id;
	Genode::Trace::Execution_time     execution_time;
	unsigned	   prio;
	unsigned	   id;
	long unsigned int  foc_id;
	size_t		   ram_quota;
	size_t		   ram_used;
};

class Mon_manager
{
	public:
		void update_info(Genode::Dataspace_capability ds_cap);
		Mon_manager();
		Genode::Dataspace_capability init_ds_cap(int num_threads);
		
	protected:
		bool core0_is_online;
		bool core1_is_online;
		int num_cores;
		Genode::Trace::Execution_time idle0;
		Genode::Trace::Execution_time idle1;
		size_t ram_avail;
		int num_threads;
};
}
