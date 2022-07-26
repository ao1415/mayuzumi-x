<template>
  <div class="h-100 position-relative" ref="Scroll">
    <slot></slot>
  </div>
</template>

<script lang="ts">
import { defineComponent, onMounted, onUnmounted, ref } from "vue";
import Simplebar from "simplebar";

export default defineComponent({
  name: "SimpleScroll",

  setup() {
    const Scroll = ref<HTMLElement>();
    const sb = ref<Simplebar>();

    onMounted(() => {
      if (Scroll.value) {
        sb.value = new Simplebar(Scroll.value, { autoHide: false });
      }
    });

    onUnmounted(() => {
      sb.value?.unMount();
    });

    return { Scroll, sb };
  },
});
</script>
