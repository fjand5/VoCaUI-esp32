<template>
  <div class="panel">
    <el-tabs
      tab-position="top"
      type="border-card"
      :stretch="true"
      v-model="selectedTab"
    >
      <template v-for="(tab, index) in collectTabs">
        <el-tab-pane :key="index" :label="tab" :name="tab">
          <el-row :gutter="20" justify="start">
            <template v-for="(compt, index) in getComponentsByTab(tab)">
              <component
                :key="index"
                :is="compt.type"
                :compt="compt"
              ></component>
            </template>
          </el-row>
        </el-tab-pane>
      </template>
    </el-tabs>
  </div>
</template>

<script>
import EspButton from "../components/EspButton";
import EspSwitch from "../components/EspSwitch";
import EspSlider from "../components/EspSlider";
import EspInput from "../components/EspInput";
import EspColorPicker from "../components/EspColorPicker";
import EspSelect from "../components/EspSelect";
import { mapGetters } from "vuex";
export default {
  data() {
    return {
      selectedTab: null,
    };
  },
  components: {
    EspButton,
    EspSwitch,
    EspSlider,
    EspInput,
    EspColorPicker,
    EspSelect
  },
  computed: {
    ...mapGetters(["getRender"]),
    collectTabs: function () {
      let ret = new Set();
      this.getRender.forEach((elm) => {
        ret.add(elm.tab);
      });
      return ret;
    },
  },
  mounted: function () {
    this.$store.dispatch("requireRenderData").then(() => {
      this.getRender.some((elm) => {
        this.selectedTab = elm.tab;
        return true;
      });
      this.$store.dispatch('initCommand')
    });
  },
  watch: {},
  methods: {
    getComponentsByTab: function (tab) {
      let ret = this.getRender.filter((elm) => {
        return elm.tab == tab;
      });
      return ret;
    },
  },
};
</script>
<style scoped>
</style>