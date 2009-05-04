/*
**  Windstille - A Sci-Fi Action-Adventure Game
**  Copyright (C) 2009 Ingo Ruhnke <grumbel@gmx.de>
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**  
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**  
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <gtkmm/main.h>

#include "device_list_dialog.hpp"
#include "device_property_dialog.hpp"
#include "joystick.hpp"
#include "main.hpp"

Main* Main::current_ = 0;

Main::Main()
{
  current_ = this;
}

Main::~Main()
{
}

void
Main::show_device_list_dialog()
{
  DeviceListDialog window;
  window.show_all();
  Gtk::Main::run(window);
}

void
Main::show_device_property_dialog(const std::string& filename)
{
  std::cout << "Main::show_device_property_dialog: " << filename << std::endl;

  Joystick joystick(filename);
  DevicePropertyDialog prop(joystick);
  prop.show_all();
  prop.run();
}

int
Main::main(int argc, char** argv)
{
  typedef std::vector<std::string> DeviceFiles;
  DeviceFiles device_files;

  for(int i = 1; i < argc; ++i)
    {
      device_files.push_back(argv[i]);
    }

  Gtk::Main kit(&argc, &argv);

  if (device_files.empty())
    {
      show_device_list_dialog();
    }
  else
    {
      for(DeviceFiles::iterator i = device_files.begin(); i != device_files.end(); ++i)
        {
          show_device_property_dialog(*i);
        }
    }
}

int main(int argc, char** argv)
{
  Main app;
  return app.main(argc, argv);
}

/* EOF */