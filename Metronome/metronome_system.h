//
//  metronome_system.h
//  Metronome
//
//  Created by Carlos Azuaje on 08/10/2022.
//

#ifndef metronome_system_h
#define metronome_system_h

#include "/opt/local/include/fluidsynth.h"

#include <stdio.h>

void start_metronome(const char *sount_font_path, unsigned int bpm);
void finish_metronome();

#endif /* metronome_system_h */
