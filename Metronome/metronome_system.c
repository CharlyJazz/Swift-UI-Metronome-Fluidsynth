//
//  metronome_system.c
//  Metronome
//
//  Created by Carlos Azuaje on 08/10/2022.
//

#include "metronome_system.h"

#include "/opt/local/include/fluidsynth.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define TEMPO 120 /* default tempo, beats per minute */

fluid_synth_t* synth;
fluid_audio_driver_t* audiodriver;
fluid_sequencer_t* sequencer;
fluid_settings_t *settings;

short synth_destination, client_destination;
unsigned int already_stopped = 1;
unsigned int time_marker;
unsigned int note_duration = 60000 / TEMPO;
/* metronome click/bell */
unsigned int weak_note = 69;
unsigned int strong_note = 72;
/* number of notes in one pattern */
unsigned int pattern_size = 4;
 
// prototype
void
sequencer_callback(unsigned int time, fluid_event_t *event,
                   fluid_sequencer_t *seq, void *data);

// Metronome exammple start
/* schedule a note on message */
void
schedule_noteon(int chan, short key, unsigned int ticks)
{
    fluid_event_t *ev = new_fluid_event();
    fluid_event_set_source(ev, -1);
    fluid_event_set_dest(ev, synth_destination);
    fluid_event_note(ev, chan, key, 100, 5);
    fluid_sequencer_send_at(sequencer, ev, ticks, 1);
    delete_fluid_event(ev);
}
 
/* schedule a timer event (shall trigger the callback) */
void
schedule_timer_event(void)
{
    fluid_event_t *ev = new_fluid_event();
    fluid_event_set_source(ev, -1);
    fluid_event_set_dest(ev, client_destination);
    fluid_event_timer(ev, NULL);
    fluid_sequencer_send_at(sequencer, ev, time_marker, 1);
    delete_fluid_event(ev);
}



/* schedule the metronome pattern */
void
schedule_pattern(void)
{
    unsigned int i;
    int note_time;
    note_time = time_marker;
    int channel = 1;
    for(i = 0; i < pattern_size; ++i)
    {
        schedule_noteon(channel, i ? weak_note : strong_note, note_time);
        note_time += note_duration;
    }
 
    time_marker = note_time;
}

void createsynth()
{
    fluid_settings_t* settings;
    settings = new_fluid_settings();
    synth = new_fluid_synth(settings);
    audiodriver = new_fluid_audio_driver(settings, synth);
    sequencer = new_fluid_sequencer2(0);
    synth_destination = fluid_sequencer_register_fluidsynth(sequencer, synth);
    client_destination = fluid_sequencer_register_client(sequencer, "Metronome", sequencer_callback, NULL);
}

void deletesynth()
{
    delete_fluid_sequencer(sequencer);
    delete_fluid_audio_driver(audiodriver);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);
}

void loadsoundfont(const char *filename_path)
{
    int fluid_res;
    // put your own path here
    fluid_res = fluid_synth_sfload(synth, filename_path, 1);
}

void
sequencer_callback(unsigned int time, fluid_event_t *event,
                   fluid_sequencer_t *seq, void *data)
{
    schedule_timer_event();
    schedule_pattern();
}
// Metronome exammple end
 
void start_metronome(const char *sount_font_path, unsigned int bpm) {
    printf("Start metronome");
    already_stopped = 0;
    note_duration = 60000 / bpm;
    createsynth();
    loadsoundfont(sount_font_path);
    /* get the current time in ticks */
    time_marker = fluid_sequencer_get_tick(sequencer);
    /* schedule patterns */
    schedule_pattern();
    schedule_timer_event();
}


void finish_metronome()
{
    if (already_stopped == 0) {
        deletesynth();
        already_stopped = 1;
        printf("Finish metronome");
    }
}
