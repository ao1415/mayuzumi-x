<template>
  <Teleport to="body">
    <div class="modal" tabindex="-1" ref="BootModal">
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
            <slot></slot>
          </div>
        </div>
      </div>
    </div>
  </Teleport>
</template>

<script lang="ts">
import { defineComponent, onMounted, onUnmounted, ref } from "vue";
import { Modal } from "bootstrap";

export default defineComponent({
  name: "BootModal",

  setup() {
    const BootModal = ref<HTMLElement>();
    const myModal = ref<Modal>();

    onMounted(() => {
      if (BootModal.value) {
        myModal.value = new Modal(BootModal.value);
      }
    });

    onUnmounted(() => {
      myModal.value?.dispose();
    });

    return {
      BootModal,
      myModal,
    };
  },

  methods: {
    show() {
      this.myModal?.show();
    },
    hide() {
      this.myModal?.hide();
    },
  },
});
</script>

<style scoped>
.modal-header-dark {
  background-color: #2c3034;
  border-bottom: none;
}
</style>
