// Copyright (c) 2020-2021 Javier Castro - jcastro0x@gmail.com.
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights 
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
// copies of the Software, and to permit persons to whom the Software is 
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in 
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
// SOFTWARE.

#include <gossip.h>
#include <interpreter.h>
#include <log.h>

#include <chrono>
#include <mutex>

#include <iostream>


Gossip::Gossip(const Interpreter* interpreter)
: m_interpreter(interpreter)
{
}

Gossip::~Gossip()
{
    thread_update.join();
}

void Gossip::run()
{
    thread_update = std::thread(std::bind(&Gossip::update, this));
    Log::print("Gossip running...");
}

void Gossip::update()
{
    using namespace std::chrono_literals;
    while(m_interpreter->isRunning())
    {
        std::this_thread::sleep_for(500ms); //we don't want to drain all CPU!!
        //std::lock_guard<std::mutex> a;

        const auto& mm = m_interpreter->getMemoryManager();
        ECatastrophes c = mm.getActiveCastastrophe();
        if(c != ECatastrophes::None && c != m_lastDetectedCatastrophe)
        {
            m_lastDetectedCatastrophe = c;
            Log::print("New castastrophe detected!");
            Log::print(mm.getCastastropheName(c).c_str());
        }
    }
}
