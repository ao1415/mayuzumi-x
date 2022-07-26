<template>
  <div class="main vh-100 text-white bg-dark">
    <div class="container-fluid">
      <div class="d-flex vh-100" :class="{ 'flex-column': breakpoint }">
        <div :class="{ 'flex-grow-1': !breakpoint, 'live-video': breakpoint }">
          <div class="ratio ratio-16x9" :class="{ 'h-100': breakpoint }">
            <div class="overflow-hidden">
              <video
                class="video-js vjs-big-play-centered w-100 h-100"
                playsinline
                ref="LiveVideo"
              >
                <source src="MayuzumiX.mp4" />
              </video>
            </div>
          </div>
        </div>
        <div
          class="overflow-hidden"
          :class="{ 'flex-grow-1': breakpoint, 'live-list': !breakpoint }"
        >
          <LiveListVue></LiveListVue>
        </div>
      </div>
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent, onMounted, ref } from "vue";
import videojs, { VideoJsPlayer } from "video.js";
import LiveListVue from "@/components/LiveList.vue";

export default defineComponent({
  name: "MainView",
  components: { LiveListVue },

  setup() {
    const breakpoint = ref<boolean>(false);
    const LiveVideo = ref<HTMLElement>();
    const player = ref<VideoJsPlayer>();

    onMounted(() => {
      if (LiveVideo.value) {
        player.value = videojs(LiveVideo.value, {
          controls: true,
          controlBar: {
            volumePanel: {
              inline: false,
              volumeControl: {
                vertical: true,
              },
            },
          },
        });
      }

      const onResize = () => {
        const width = window.innerWidth;
        breakpoint.value = width < 992;
      };
      onResize();
      window.addEventListener("resize", onResize);
    });

    return { breakpoint, LiveVideo, player };
  },
});
</script>

<style scoped>
.live-video {
  max-height: 40%;
}
.live-list {
  width: 40%;
}
</style>
