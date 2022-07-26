<template>
  <router-view />
</template>

<script setup lang="ts">
const setFillHeight = () => {
  const vh = window.innerHeight * 0.01;
  document.documentElement.style.setProperty("--vh", `${vh}px`);
};

let vw = window.innerWidth;

window.addEventListener("resize", () => {
  if (vw === window.innerWidth) {
    return;
  }

  vw = window.innerWidth;
  setFillHeight();
});

// 初期化
setFillHeight();
</script>

<style>
.js-vh-100 {
  height: calc(var(--vh, 1vh) * 100);
}
</style>
