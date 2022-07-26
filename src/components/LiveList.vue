<template>
  <div class="h-100 position-relative">
    <SimpleScrollVue>
      <table class="table table-dark table-striped table-hover mb-0">
        <thead>
          <tr>
            <th>日付</th>
            <th>タイトル</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="(data, index) in liveList" :key="index">
            <td>
              <span>{{ data.date }}</span>
            </td>
            <td v-if="Array.isArray(data.id)">
              <div v-for="index in data.id.length" :key="index" class="d-flex">
                <div class="flex-grow-1">
                  <a
                    class="text-reset"
                    :href="getLink(data.platform, data.id[index - 1])"
                    target="_blank"
                    rel="noopener noreferrer"
                    @click.stop=""
                    >{{ data.title[index - 1] }}</a
                  >
                </div>
                <div
                  class="d-flex align-items-center"
                  :class="{
                    'mb-1': index == 1,
                    'my-1': index != 1 && index != data.id.length,
                    'mt-1': index == data.id.length,
                  }"
                >
                  <button
                    class="btn btn-outline-light btn-sm text-nowrap play-icon"
                    @click.left="
                      showMovieModal(data.platform, data.id[index - 1])
                    "
                  >
                    表示
                  </button>
                </div>
              </div>
            </td>
            <td v-else>
              <div class="d-flex">
                <div class="flex-grow-1">
                  <a
                    class="text-reset"
                    :href="getLink(data.platform, data.id)"
                    target="_blank"
                    rel="noopener noreferrer"
                    @click.stop=""
                    >{{ data.title }}</a
                  >
                </div>
                <div class="d-flex align-items-center">
                  <button
                    v-if="data.id != ''"
                    class="btn btn-outline-light btn-sm text-nowrap play-icon"
                    @click.left="showMovieModal(data.platform, data.id)"
                  >
                    表示
                  </button>
                </div>
              </div>
            </td>
          </tr>
        </tbody>
      </table>
    </SimpleScrollVue>
    <div class="position-absolute bottom-0 start-0 lh-1 ps-3 pb-3 d-none">
      <button class="btn btn-outline-light rounded-circle p-0 border-2 filter">
        <i class="bi bi-filter"></i>
      </button>
    </div>
  </div>

  <BootModalVue ref="MovieModal">
    <div class="ratio ratio-16x9">
      <!-- youtube -->
      <iframe
        v-if="selectedPlatform == 'youtube'"
        class="w-100 h-100 border-0"
        :src="liveUrl"
        title="YouTube video player"
      ></iframe>
      <!-- niconico -->
      <iframe
        v-if="selectedPlatform == 'nicovideo'"
        class="w-100 h-100 border-0"
        :src="liveUrl"
        title="niconico video player"
      ></iframe>
      <!-- twitcasting -->
      <iframe
        v-if="selectedPlatform == 'twitcasting'"
        class="w-100 h-100 border-0"
        :src="liveUrl"
        title="twitcas video player"
      ></iframe>
      <!-- bilibili -->
      <iframe
        v-if="selectedPlatform == 'bilibili'"
        class="w-100 h-100 border-0"
        :src="liveUrl"
        title="bilibili video player"
      >
      </iframe>
    </div>
  </BootModalVue>

  <BootModalVue></BootModalVue>
</template>

<script lang="ts">
import { computed, defineComponent, ref } from "vue";
import BootModalVue from "@/components/BootModal.vue";
import SimpleScrollVue from "@/components/SimpleScroll.vue";

type PlatformType = "" | "youtube" | "nicovideo" | "twitcasting" | "bilibili";
type LiveJson = {
  platform: PlatformType;
  date: string;
  id: string;
  title: string;
  members: string[];
}[];

export default defineComponent({
  name: "LiveList",

  components: {
    BootModalVue,
    SimpleScrollVue,
  },

  setup() {
    const liveList = ref<LiveJson>([]);
    liveList.value = require("@/assets/live.json");

    const selectedPlatform = ref<PlatformType>("");
    const selectedId = ref<string>("");

    const liveUrl = computed(() => {
      switch (selectedPlatform.value) {
        case "youtube":
          return `https://www.youtube.com/embed/${selectedId.value}`;

        case "nicovideo":
          return `https://embed.nicovideo.jp/watch/${selectedId.value}`;

        case "twitcasting":
          return `https://twitcasting.tv/${selectedId.value}`.replace(
            "movie",
            "embeddedplayer"
          );

        case "bilibili":
          return `//player.bilibili.com/player.html?bvid=${selectedId.value}`;

        default:
          return "";
      }
    });

    const getLink = (platform: PlatformType, id: string): string => {
      switch (platform) {
        case "youtube":
          return `https://www.youtube.com/watch?v=${id}`;

        case "nicovideo":
          return `https://www.nicovideo.jp/watch/${id}`;

        case "twitcasting":
          return `https://twitcasting.tv/${id}`;

        case "bilibili":
          return `https://www.bilibili.com/video/${id}/`;

        default:
          return "";
      }
    };

    return {
      liveList,
      selectedPlatform,
      selectedId,
      liveUrl,
      getLink,
    };
  },

  methods: {
    showMovieModal(platform: PlatformType, id: string) {
      this.selectedPlatform = platform;
      this.selectedId = id;

      const modal = this.$refs.MovieModal as InstanceType<typeof BootModalVue>;
      modal.show();
    },
    hideMovieModal() {
      this.selectedPlatform = "";
      this.selectedId = "";

      const modal = this.$refs.MovieModal as InstanceType<typeof BootModalVue>;
      modal.hide();
    },
  },
});
</script>

<style scoped>
.table {
  width: calc(100% - 11px);
}
tr {
  height: 3em;
}
.filter {
  width: 3em;
  height: 3em;
}
.filter > i {
  font-size: 2em;
}
</style>
