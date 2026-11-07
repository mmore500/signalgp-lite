const fs = require('fs');
const path = require('path');
const { JSDOM, VirtualConsole } = require('jsdom');

const web = path.resolve(process.argv[2]);
const logs = [];
const virtualConsole = new VirtualConsole();
virtualConsole.on('log', (msg) => logs.push(String(msg)));

JSDOM.fromFile(path.join(web, 'signalgp-lite.html'), {
  runScripts: 'dangerously',
  resources: 'usable',
  virtualConsole,
  // jsdom can't fetch the .wasm
  beforeParse(window) {
    window.Module = {
      wasmBinary: fs.readFileSync(path.join(web, 'signalgp-lite.wasm')),
    };
  },
}).then((dom) => setTimeout(() => {
  const html = dom.serialize().includes('Hello, browser!');
  const console_ = logs.some((msg) => msg.includes('Hello, console!'));
  console.log(`Hello, browser! ${html ? 'matched' : 'MISSING'}`);
  console.log(`Hello, console! ${console_ ? 'matched' : 'MISSING'}`);
  process.exit(html && console_ ? 0 : 1);
}, 1000));
