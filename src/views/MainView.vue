<template>
  <div class="main vh-100 text-white bg-dark">
    <div class="container-fluid">
      <div class="d-flex vh-100" :class="{ 'flex-column': breakpoint }">
        <div :class="{ 'flex-grow-1': !breakpoint, 'live-video': breakpoint }">
          <div class="ratio ratio-16x9" :class="{ 'h-100': breakpoint }">
            <div class="overflow-hidden">
              <video
                class="video-js vjs-big-play-centered w-100 h-100"
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
          <div class="h-100 position-relative" ref="LiveTable">
            <LiveListVue></LiveListVue>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent, onMounted, onUnmounted, ref } from "vue";
import Simplebar from "simplebar";
import videojs, { VideoJsPlayer } from "video.js";
import LiveListVue from "@/components/LiveList.vue";

export default defineComponent({
  name: "MainView",
  components: { LiveListVue },

  setup() {
    const LiveTable = ref<HTMLElement>();
    const ps = ref<Simplebar>();
    const breakpoint = ref<boolean>(false);
    const LiveVideo = ref<HTMLElement>();
    const player = ref<VideoJsPlayer>();

    onMounted(() => {
      if (LiveTable.value) {
        ps.value = new Simplebar(LiveTable.value, { autoHide: false });
      }

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

    onUnmounted(() => {
      ps.value?.unMount();
    });

    return { LiveTable, ps, breakpoint, LiveVideo, player };
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
