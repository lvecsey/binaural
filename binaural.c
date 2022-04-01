/*
    Create binaural audio as raw audio output, convert with sox or audacity
    Copyright (C) 2022  Lester Vecsey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
				
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <math.h>

#include <sys/mman.h>

#include <errno.h>

enum { LEFT, RIGHT };

typedef struct {

  double channels[2];

} sample;
  

int main(int argc, char *argv[]) {

  double stereo_freqs[2];

  long int samplerate;

  double duration;

  int fd;
  void *m;
  mode_t mode;

  char *output_fn;

  sample *samples;

  long int num_samples;

  size_t fsize;

  int retval;

  double radians;
  
  stereo_freqs[0] = 400.0;
  stereo_freqs[1] = 440.0;

  duration = 20.0;

  output_fn = argc>1 ? argv[1] : "binaural.raw";

  mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

  samplerate = 192000;

  num_samples = samplerate * duration;

  fd = open(output_fn, O_RDWR | O_CREAT | O_TRUNC, mode);
  if (fd == -1) {
    perror("open");
    return -1;
  }

  fsize = num_samples * sizeof(sample);
  
  retval = ftruncate(fd, fsize);
  if (retval == -1) {
    perror("ftruncate");
    return -1;
  }

  m = mmap(NULL, fsize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  if (m == MAP_FAILED) {
    perror("mmap");
    return -1;
  }

  samples = (sample*) m;
  
  long int sampleno;

  double vol;

  vol = 0.9875;
  
  for (sampleno = 0; sampleno < num_samples; sampleno++) {

    radians = (2.0 * M_PI * sampleno * stereo_freqs[0] * duration) / (num_samples - 1);
    samples[sampleno].channels[LEFT] = vol * sin(radians);

    radians = (2.0 * M_PI * sampleno * stereo_freqs[1] * duration) / (num_samples - 1);
    samples[sampleno].channels[RIGHT] = vol * sin(radians);

  }

  retval = munmap(m, fsize);
  if (retval == -1) {
    perror("munmap");
    return -1;
  }

  retval = close(fd);
  if (retval == -1) {
    perror("close");
    return -1;
  }
  
  return 0;

}
