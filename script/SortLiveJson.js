const fs = require("fs/promises");

/**
 * @typedef {{
 *   platform: string;
 *   date: string;
 *   id: string | string[];
 *   title: string | string[];
 *   members: string[];
 * }} LiveType
 */

async function main() {
  const json = await fs.readFile("./src/assets/live.json");

  /** @type {LiveType[]} */
  const data = JSON.parse(json.toString());

  data.sort((a, b) => {
    if (a.date < b.date) {
      return -1;
    } else if (b.date < a.date) {
      return 1;
    } else {
      return 0;
    }
  });

  for (const live of data) {
    live.members.sort();
  }

  console.debug(JSON.stringify(data, null, 2));
}

main();
