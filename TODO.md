# TODO / Project Roadmap

Use this as the public GitHub checklist for getting the Smart Light Bar Controller from prototype to a cleaner release.

## High priority

- [ ] Confirm the official controller board.
  - [ ] Arduino Mega 2560 if using pins 41-49.
  - [ ] Compact controller such as DFRobot Beetle only if the pin map and code are updated.
- [ ] Remove blocking behavior.
  - [ ] Replace `delay()` in buzzer functions with a non-blocking beep scheduler.
  - [ ] Replace `while(true)` GPS failure halt with a non-blocking error state.
- [ ] Finish GPS update behavior.
  - [ ] Configure GPS for 10 Hz updates if the module supports it.
  - [ ] Or add calculated/interpolated speed behavior between GPS updates.
- [ ] Implement final button behavior.
  - [ ] 3-second hold: sound 2 tones and set high-speed threshold at the 3-second mark.
  - [ ] 10-second hold: sound 4 tones and set high-speed threshold at the 10-second mark.
  - [ ] Do nothing on release after the threshold has already been handled.
  - [ ] Store threshold in EEPROM.
- [ ] Finalize low-speed behavior.
  - [ ] If default high speed is below 10 mph, use settings 1-3 only.
- [ ] Finish accelerometer behavior.
  - [ ] Turn blue LED on when inactivity is triggered.
  - [ ] Turn blue LED off when activity returns.
  - [ ] Add clearly marked callback sections for custom activity/inactivity behavior.
- [ ] Finish error LED behavior.
  - [ ] Flash red LED 500 ms on / 500 ms off when GPS speed is unavailable.
  - [ ] Flash red LED for non-matching lighting-controller signals.
- [ ] Turn off speed-setting LEDs when GPS mode is inactive.

## Documentation

- [ ] Add a wiring diagram.
- [ ] Add photos of the prototype wiring from multiple angles.
- [ ] Add a table of all lighting controller pulse timings.
- [ ] Add bench-test instructions using Serial Monitor.
- [ ] Add a short demo video or animated GIF.
- [ ] Add install notes for power, ground, fuse, enclosure, and signal wiring.

## Repo hygiene

- [ ] Add a license.
- [ ] Add a `CONTRIBUTING.md` if you want outside pull requests.
- [ ] Add GitHub issue templates for bug reports and hardware compatibility reports.
- [ ] Add a release tag once the project has one known-good working version.
- [ ] Consider moving PCB files into a cleaner `hardware/` folder in a future cleanup.
