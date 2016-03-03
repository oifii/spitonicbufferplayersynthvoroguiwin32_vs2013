/*
 * Copyright (c) 2015-2016 Stephane Poirier
 *
 * stephane.poirier@oifii.org
 *
 * Stephane Poirier
 * 3532 rue Ste-Famille, #3
 * Montreal, QC, H2X 2L1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef BufferPlayerExpSynth_h
#define BufferPlayerExpSynth_h

#include "Tonic.h"
#include <functional>

#include <sndfile.hh>

using namespace Tonic;

#define INT_TO_STRING( x ) dynamic_cast< std::ostringstream & >( \
	(std::ostringstream() << std::dec << x)).str()

class BufferPlayerExpSynth : public Synth{

public:
	BufferPlayerExpSynth(){

		//#if TONIC_HAS_CPP_11
#if 1
		ControlGenerator bpm = addParameter("tempo", 120).min(1).max(300);
		//SampleTable buffer = loadAudioFile("D:\\oifii-org\\httpdocs\\ha-org\\had\\dj-oifii\\BASSDRUMS (House Minimal Trance D&B Techno) PACK 1\\BD (1).wav",2);
		SndfileHandle file;
		//file = SndfileHandle("D:\\oifii-org\\httpdocs\\ha-org\\had\\dj-oifii\\BASSDRUMS (House Minimal Trance D&B Techno) PACK 1\\BD (1).wav");
		file = SndfileHandle("D:\\oifii-org\\httpdocs\\ha-org\\had\\dj-oifii\\BASSDRUMS (House Minimal Trance D&B Techno) PACK 1\\BD (7).wav");
		assert(file.samplerate() == 44100);
		assert(file.channels() == 2);
		SampleTable buffer(file.frames(),file.channels());
		file.read(buffer.dataPointer(), file.frames()*file.channels());
		BufferPlayer bPlayer;
		//bPlayer.setBuffer(buffer).loop(false).trigger(ControlMetro().bpm(120));
		bPlayer.setBuffer(buffer).loop(false).trigger(ControlMetro().bpm(bpm));

		SndfileHandle file2;
		file2 = SndfileHandle("D:\\oifii-org\\httpdocs\\ha-org\\had\\dj-oifii\\Function.Loops.Spirit.Progressive.Trance.and.Psy.WAV\\DRUMS\\DRUM_01_HIHAT_138bpm(single-128ms).wav");
		assert(file2.samplerate() == 44100);
		assert(file2.channels() == 2);
		SampleTable buffer2(file2.frames(), file2.channels());
		file2.read(buffer2.dataPointer(), file2.frames()*file2.channels());
		BufferPlayer bPlayer2;
		//bPlayer2.setBuffer(buffer2).loop(false).trigger(ControlMetro().bpm(120 * 4));
		bPlayer2.setBuffer(buffer2).loop(false).trigger(ControlMetro().bpm(bpm * 4));

		StereoDelay delay = StereoDelay(3.0f, 3.0f, 3.0f, 3.0f)
			//.delayTimeLeft(0.5 + SineWave().freq(0.2) * 0.01)
			.delayTimeLeft(addParameter("delay_left", 0.5).min(0.0).max(3.0))
			//.delayTimeRight(0.55 + SineWave().freq(0.23) * 0.01)
			.delayTimeRight(addParameter("delay_right", 0.55).min(0.0).max(3.0))
			//.feedback(0.3)
			.feedback(addParameter("delay_feedback", 0.5).min(0.0).max(1.0))
			.dryLevel(addParameter("delay_drylevel", 0.5).min(0.0).max(1.0))
			//.wetLevel(0.2);
			.wetLevel(addParameter("delay_wetlevel", 0.5).min(0.0).max(1.0));

		//setOutputGen(bPlayer + bPlayer2); 
		setOutputGen(delay.input(bPlayer + bPlayer2)); 
		setLimitOutput(false);


#else

#pragma message("C++11 Support not available - BufferPlayerExpSynth disabled")

#endif
	}
};

//TONIC_REGISTER_SYNTH(BufferPlayerExpSynth)

#endif
