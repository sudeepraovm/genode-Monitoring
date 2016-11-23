#pragma once

#include <base/signal.h>
#include <monitoring/monitoring_session.h>
#include <os/attached_ram_dataspace.h>
#include <os/server.h>
#include <root/component.h>
#include <timer_session/connection.h>
#include <util/string.h>
#include <cap_session/connection.h>
#include <trace_session/connection.h>

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

struct Monitoring_session_component : Genode::Rpc_object<Monitoring_session>
{
public:
	Monitoring_session_component(Server::Entrypoint& ep);
	virtual ~Monitoring_session_component();
	void update_info();


protected:
	Server::Entrypoint& _ep;
	Genode::Cap_connection _cap;
	bool core0_is_online;
	bool core1_is_online;
	int num_cores;
	Genode::Trace::Execution_time idle0;
	Genode::Trace::Execution_time idle1;
	size_t ram_avail;
	int num_threads;
	Monitoring_object threads[];
};

struct Monitoring_root_component : Genode::Root_component<Monitoring_session_component>
{
public:
	Monitoring_root_component(Server::Entrypoint* ep, Genode::Allocator *allocator) :
		Genode::Root_component<Monitoring_session_component>(&ep->rpc_ep(), allocator),
		_ep(*ep)
	{
		PDBG("Creating root component.");
	}

protected:
	Server::Entrypoint& _ep;
	Monitoring_session_component* _create_session(const char *args)
	{
		PDBG("Creating Monitoring session.");
		return new (md_alloc()) Monitoring_session_component(_ep);
	}
};
