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

  /** @type {string[]} */
  let members = [];
  for (const live of data) {
    for (const member of live.members) {
      members.push(member);
    }
  }
  members.sort();
  members = Array.from(new Set(members));
  for (const member of members) {
    console.debug(member);
  }
}

main();
