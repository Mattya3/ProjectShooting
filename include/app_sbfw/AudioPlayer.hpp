#pragma once
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <bits/stdc++.h>
#include <unistd.h> //sleep関数用
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
using namespace std;

class MyThread {
  private:
    thread t_;
    bool is_working = false;
    function<void(void)> task;

  public:
    MyThread(function<void(void)> task) : task(task) {}
    MyThread() = default;
    void Start() {
        if(!is_working) {
            cout << "start task" << endl;
            if(t_.joinable())
                t_.detach();
            t_ = thread([&]() {
                is_working = true;
                task();
                is_working = false;
            });
        } else {
            cout << "Now Working" << endl;
        }
    }
    void Join() {
        if(t_.joinable())
            t_.join();
    }
    ~MyThread() {
        if(t_.joinable())
            t_.join();
    }
};
namespace {
int souce_cnt = 0;
bool is_inited_audio = false;
} // namespace
class AudioPlayer {
    const static int audio_num = 5;
    static ALuint buffer[audio_num], source[audio_num];

  private:
    mutex mtx;

    ALshort data[22050];
    int this_audio_id;

  public:
    void Play() { mt.Start(); }
    MyThread mt;
    void PrepareAudioPlayer() {}
    AudioPlayer(int height)
        : mt([&]() {
              alSourcePlay(source[this_audio_id]);
              this_thread::sleep_for(chrono::milliseconds(100));
              alSourceStop(source[this_audio_id]);
          }) {

        if(!is_inited_audio) {
            InitOpenAL();
            is_inited_audio = true;
        }
        this_audio_id = souce_cnt++;
        // 信号を生成する
        for(int i = 0; i < 22050; ++i) {
            data[i] = sin(i * 3.14159 * 2 * height / 22050) * 32767;
        }
        // 信号をバッファに入れる // データを登録し、登録時のidがbuffer
        alBufferData(buffer[this_audio_id], AL_FORMAT_MONO16, data,
                     sizeof(data), 22050);

        // バッファからソースを作る 器にデータをつける
        alSourcei(source[this_audio_id], AL_BUFFER, buffer[this_audio_id]);
    }

  private:
    void InitOpenAL() {
        ALCdevice *device;
        ALCcontext *context;
        // デバイスを開く
        device = alcOpenDevice(NULL);
        // コンテキストを生成
        context = alcCreateContext(device, NULL);
        // 使用するコンテキストの指定
        alcMakeContextCurrent(context);
        alGenBuffers(audio_num, buffer);
        // ソースを生成 // オーディオの器sourceを作成
        alGenSources(audio_num, source);
    }
};
