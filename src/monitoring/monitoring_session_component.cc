#include "monitoring_session_component.h"
#include <timer_session/connection.h>
#include <base/env.h>
#include <base/printf.h>
#include <base/process.h>
#include <util/xml_node.h>
#include <util/xml_generator.h>
#include <string>
#include <util/string.h>
#include <trace_session/connection.h>
#include <os/config.h>

Monitoring_session_component::Monitoring_session_component(Server::Entrypoint& ep) :
	_ep{ep},
	_cap{}
{
}

Monitoring_session_component::~Monitoring_session_component()
{
}

void Monitoring_session_component::update_info()
{
	static Timer::Connection timer;
	static Genode::Trace::Connection trace(1024*4096, 64*4096, 0);
	Genode::Trace::Subject_id subjects[num_threads];
	size_t num_subjects = trace.subjects(subjects, num_threads);
	Genode::Trace::RAM_info init;

	for (size_t i = 0; i < num_subjects; i++) {
		Genode::Trace::CPU_info cpu_info = trace.cpu_info(subjects[i]);
		Genode::Trace::RAM_info ram_info = trace.ram_info(subjects[i]);
		Genode::Trace::SCHEDULER_info scheduler_info = trace.scheduler_info(subjects[i]);
		if(Genode::strcmp(cpu_info.session_label().string(), "init")!=0) {
       			threads[i].session_label=cpu_info.session_label();
			threads[i].thread_name=cpu_info.thread_name();
			threads[i].prio=cpu_info.prio();
			threads[i].execution_time=cpu_info.execution_time();
			threads[i].id=cpu_info.id();
			threads[i].foc_id=scheduler_info.foc_id();
			threads[i].ram_used=ram_info.ram_used();
			threads[i].ram_quota=ram_info.ram_quota();
		}else {
			init=ram_info;
		}
					
	}
	Genode::Trace::SCHEDULER_info scheduler_info = trace.scheduler_info(subjects[0]);
	ram_avail=init.ram_quota();
	idle0=scheduler_info.idle();
	core0_is_online=scheduler_info.core0_is_online();
	core1_is_online=scheduler_info.core1_is_online();
	num_cores=scheduler_info.num_cores();
}
