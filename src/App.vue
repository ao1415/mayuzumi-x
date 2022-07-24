<template>
  <router-view />
</template>

<script lang="ts">
import { defineComponent } from "vue";

export default defineComponent({
  mounted() {
    console.debug(this.$router);
    console.debug(this.$router.getRoutes());
  },
});
</script>

<style></style>
