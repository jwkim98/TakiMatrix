//
// Created by jwkim98 on 19. 1. 13.
//

#include "../../../includes/cpu_emulator/front_end/instruction_queue.hpp"

namespace TakiMatrix::processor {
    instruction_queue::instruction_queue(size_t queue_size)
            :m_default_queue_size(queue_size) { }

    void instruction_queue::push(isa& instruction)
    {
        std::unique_lock<std::mutex> lock(instruction_queue_mtx);
        m_cond.wait(lock, [this]() {
            return m_instruction_queue.size()<m_default_queue_size;
        });
        m_instruction_queue.emplace_back(instruction);
        lock.unlock();
        m_cond.notify_all();
    }

    isa instruction_queue::pop()
    {
        std::unique_lock<std::mutex> lock(instruction_queue_mtx);
        m_cond.wait(lock, [this]() {
            return m_instruction_queue.size()<m_default_queue_size;
        });
        isa instruction = m_instruction_queue.front();
        m_instruction_queue.pop_front();
        lock.unlock();
        m_cond.notify_all();
    }

} // namespace TakiMatrix::processor