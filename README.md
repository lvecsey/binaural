
*Overview*

Generate a pair of sine waves, at slightly different frequencies. 400hz in the left channel, and 440hz in the right channel, for a difference of 40hz.

Use sox conversion to go from 192000 samplerate down to 48000 samplerate.

Final output is a stereo WAV file.

*Compiling*

```console
make binaural
```

*Run*

```console
./binaural
make binaural.wav
```

*Dependencies*

```console
sudo apt-get install sox
```

*License*

GPLv3

*Notes*

You can also create the binaural2.wav which is a variation that sweeps the output between the left and the right channels, 5 times per 20 seconds of audio.

[Sample image](https://phrasep.com/~lvecsey/software/binaural/binaural_screenshot.png)

![Image of output](https://phrasep.com/~lvecsey/software/binaural/binaural_screenshot.png)
