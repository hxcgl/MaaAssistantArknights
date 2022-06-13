#include "StartUpTask.h"

#include <utility>

#include "ProcessTask.h"

asst::StartUpTask::StartUpTask(AsstCallback callback, void* callback_arg)
    : PackageTask(std::move(callback), callback_arg, TaskType),
    m_start_game_task_ptr(std::make_shared<StartGameTaskPlugin>(m_callback, m_callback_arg, TaskType)),
    m_start_up_task_ptr(std::make_shared<ProcessTask>(m_callback, m_callback_arg, TaskType))
{
    m_start_up_task_ptr->set_tasks({ "StartUp" })
        .set_times_limit("ReturnToTerminal", 0)
        .set_times_limit("Terminal", 0)
        .set_times_limit("EndOfAction", 0);
    m_subtasks.emplace_back(m_start_game_task_ptr);
    m_subtasks.emplace_back(m_start_up_task_ptr);
}

bool asst::StartUpTask::set_params(const json::value& params)
{
    m_start_game_task_ptr->set_client_type(params.get("client_type", ""))
        .set_enable(params.get("start_game_enable", false));
    return true;
}