<template>
  <div class="d-flex flex-column h-100">
    <div>
      <div class="row w-100 mb-3">
        <div class="col-auto">
          <div class="form-check">
            <input
              class="form-check-input"
              type="radio"
              name="search-type"
              id="search-type-or"
              value="OR"
              v-model="searchType"
            />
            <label class="form-check-label" for="search-type-or">
              OR 検索
            </label>
          </div>
        </div>
        <div class="col-auto">
          <div class="form-check">
            <input
              class="form-check-input"
              type="radio"
              name="search-type"
              id="search-type-and"
              value="AND"
              v-model="searchType"
            />
            <label class="form-check-label" for="search-type-and">
              AND 検索
            </label>
          </div>
        </div>
      </div>

      <div class="row w-100 mb-3">
        <div class="col-auto">
          <button type="submit" class="btn btn-primary" @click="checkedAll">
            全選択
          </button>
        </div>
        <div class="col-auto">
          <button
            type="submit"
            class="btn btn-outline-primary"
            @click="uncheckedAll"
          >
            全解除
          </button>
        </div>
      </div>

      <div class="row w-100 mb-3">
        <div class="col-auto">
          <label class="visually-hidden" for="search-keyword">配信者</label>
          <div class="input-group search-text">
            <input
              type="text"
              class="form-control"
              id="search-keyword"
              placeholder="配信者"
              v-model="keyword"
            />
            <button class="btn btn-primary" type="button">
              <i class="bi bi-search"></i>
            </button>
          </div>
        </div>
      </div>
    </div>

    <div class="search-area">
      <SimpleScrollVue>
        <div v-for="(member, index) in memberList" :key="index">
          <div v-show="filter(member.names)" class="form-check form-switch">
            <input
              class="form-check-input"
              type="checkbox"
              :id="`filter-modal-${index}`"
              v-model="member.checked"
            />
            <label
              class="form-check-label name"
              :for="`filter-modal-${index}`"
              >{{ member.names }}</label
            >
          </div>
        </div>
      </SimpleScrollVue>
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent, PropType, ref } from "vue";
import SimpleScrollVue from "@/components/SimpleScroll.vue";

type FilterType = { names: string[]; checked: boolean };

export default defineComponent({
  name: "SearchModal",

  components: {
    SimpleScrollVue,
  },

  emits: {
    setFilterMember(_members: FilterType[]) {
      return _members === _members;
    },
    setFilterSearch(_isOrSearch: boolean) {
      return _isOrSearch === _isOrSearch;
    },
  },

  props: {
    allMember: Array as PropType<string[]>,
  },

  setup(props) {
    const memberList = ref<FilterType[]>([]);

    if (props.allMember != null) {
      for (const mem of props.allMember) {
        memberList.value.push({
          names: [mem],
          checked: true,
        });
      }
    }

    return { memberList };
  },

  data() {
    return {
      searchType: "",
      keyword: "",
    };
  },

  watch: {
    memberList: {
      handler: function (value: FilterType[]) {
        this.$emit("setFilterMember", value);
      },
      deep: true,
    },
    searchType: function (value: string) {
      this.$emit("setFilterSearch", value == "OR");
    },
  },

  mounted() {
    this.searchType = "OR";
  },

  methods: {
    checkedAll() {
      for (const elem of this.memberList) {
        elem.checked = true;
      }
    },
    uncheckedAll() {
      for (const elem of this.memberList) {
        elem.checked = false;
      }
    },

    filter(names: string[]): boolean {
      if (this.keyword == "") {
        return true;
      }

      for (const name of names) {
        if (name.indexOf(this.keyword) != -1) {
          return true;
        }
      }
      return false;
    },
  },
});
</script>

<style scoped>
.search-text {
  max-width: 100%;
  width: 30em;
}
.search-area {
  height: 70vh;
}
</style>
