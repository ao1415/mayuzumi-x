<template>
  <div ref="LiveTable">
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
                  class="btn btn-outline-light btn-sm text-nowrap"
                  @click.left="show(data.platform, data.id[index - 1])"
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
                  class="btn btn-outline-light btn-sm text-nowrap"
                  @click.left="show(data.platform, data.id)"
                >
                  表示
                </button>
              </div>
            </div>
          </td>
        </tr>
      </tbody>
    </table>
  </div>

  <Teleport to="body">
    <div class="modal" tabindex="-1" ref="MovieModal">
      <div class="modal-dialog modal-xl">
        <div class="modal-content border-0">
          <div class="modal-header modal-header-dark">
            <h5 class="modal-title"></h5>
            <button
              type="button"
              class="btn-close btn-close-white"
              data-bs-dismiss="modal"
              aria-label="Close"
            ></button>
          </div>
          <div class="modal-body p-0">
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
          </div>
        </div>
      </div>
    </div>
  </Teleport>
</template>

<script lang="ts">
import { computed, defineComponent, onMounted, onUnmounted, ref } from "vue";
import { Modal } from "bootstrap";

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

  setup() {
    const liveList = ref<LiveJson>([]);
    liveList.value = require("@/assets/live.json");
    liveList.value.sort((a, b) => {
      if (a.date < b.date) {
        return -1;
      } else if (b.date < a.date) {
        return 1;
      } else {
        return 0;
      }
    });

    const MovieModal = ref<HTMLElement>();
    const myModal = ref<Modal>();
    const selectedPlatform = ref<PlatformType>("");
    const selectedId = ref<string>("");

    onMounted(() => {
      if (MovieModal.value) {
        myModal.value = new Modal(MovieModal.value);
        MovieModal.value.addEventListener("hide.bs.modal", () => {
          selectedId.value = "";
        });
      }
    });

    onUnmounted(() => {
      myModal.value?.dispose();
    });

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
      MovieModal: MovieModal,
      myModal,
      selectedPlatform,
      selectedId,
      liveUrl,
      getLink,
    };
  },

  methods: {
    show(platform: PlatformType, id: string) {
      this.selectedPlatform = platform;
      this.selectedId = id;
      this.myModal?.show();
    },
    hide() {
      this.myModal?.hide();
      this.selectedPlatform = "";
      this.selectedId = "";
    },
  },
});
</script>

<style scoped>
.table {
  width: calc(100% - 11px);
}
.modal-header-dark {
  background-color: #2c3034;
  border-bottom: none;
}
</style>
