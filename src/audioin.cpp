#include "audioin.h"
#include "ext.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include "Portaudio/portaudio.h"
using namespace Oscilloscope;
using namespace std;

class Manager
{
public:
  int frame_dif;
  int frame_c;
  vector<int> lbuffer;
  vector<int> rbuffer;
};

int callback(
    const void *input,
    void *output,
    unsigned long frameCount,
    const PaStreamCallbackTimeInfo *timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData)
{
  Manager *man = (Manager *)userData;
  cout << "\n - - - - FRAME: " << frameCount << " - - - - " << endl;
  cout << " --I Size:       " << (int)(input == NULL) << " " << (int)false << endl;
  cout << " --O Size:       " << sizeof(output) << endl;
  cout << " --Current time: " << man->frame_c << endl;
  cout << " --I Started:    " << timeInfo->inputBufferAdcTime << endl;
  cout << " --O Started:    " << timeInfo->outputBufferDacTime << endl;
  cout << " --Status:       " << statusFlags << endl;

  man->frame_c += man->frame_dif;

  int *in = (int *)input;
  for (unsigned i = 0; i < man->frame_dif; i++)
  {
    man->lbuffer.push_back(*in++);
    man->rbuffer.push_back(*in++);
  }
  if (man->frame_c > 5 * 48000)
  {
    return paComplete;
  }
  return paContinue;
}

int Oscilloscope::micin()
{
  string devname = "Line In (Realtek(R) Audio)";

  PaDeviceInfo dev;
  int iResult = Pa_Initialize();
  if (iResult != paNoError)
  {
    printf("ERROR: %s\n", Pa_GetErrorText(iResult));
    return -1;
  }

  int ndev;

  ndev = Pa_GetDeviceCount();

  if (ndev < 0)
  {
    printf("ERROR: %s\n", Pa_GetErrorText(ndev));
    Pa_Terminate();
    return -1;
  }

  PaStreamParameters i_par;
  PaStreamParameters o_par;
  double srate;
  for (PaDeviceIndex i = 0; i < ndev; i++)
  {
    const PaDeviceInfo *p_devinfo = Pa_GetDeviceInfo(i);
    cout << "Device: " << p_devinfo->name
         << "\n  i: " << p_devinfo->maxInputChannels
         << "\n  o: " << p_devinfo->maxOutputChannels
         << "\n  sr: " << p_devinfo->defaultSampleRate
         << endl;

    if ((string)p_devinfo->name == devname)
    {
      cout << "THIS " << i << endl;
      srate = p_devinfo->defaultSampleRate;
      i_par = {
          i,
          p_devinfo->maxInputChannels,
          paInt32,
          p_devinfo->defaultHighInputLatency,
          NULL};
      o_par = {
          i,
          p_devinfo->maxOutputChannels,
          paInt32,
          p_devinfo->defaultLowOutputLatency,
          NULL};
      cout << "THIS" << endl;
    }
  }

  PaStream *p_stream;
  Manager man;
  man.frame_c = 0;
  man.frame_dif = (int)(srate / 100);
  man.lbuffer = {};
  man.rbuffer = {};
  cout << i_par.channelCount << endl;
  cout << i_par.device << " < " << ndev << " " << Pa_GetDeviceInfo(i_par.device)->name << endl;
  iResult = Pa_OpenStream(
      &p_stream,
      &i_par,
      NULL,
      srate,
      (unsigned long)(srate / 100),
      paNoFlag,
      &callback,
      &man);
  if (iResult != paNoError)
  {
    printf("ERROR: %s\n", Pa_GetErrorText(iResult));
    Pa_Terminate();
    return -1;
  }

  iResult = Pa_StartStream(p_stream);
  if (iResult != paNoError)
  {
    printf("ERROR: %s\n", Pa_GetErrorText(iResult));
    Pa_Terminate();
    return -1;
  }
  while (Pa_IsStreamActive(p_stream) > 0)
  {
    // * Kod som är beroende av input streamen
  }

  // for (int i : man.buffer)
  // {
  //   cout << i << ", ";
  // }
  // cout << man.buffer.size() << endl;

  Pa_Terminate();
  vecToFile("laudioin.txt", man.lbuffer);
  vecToFile("raudioin.txt", man.rbuffer);

  return 0;
}