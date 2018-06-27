# IPFA

## Theming workflow

Its a mixture of Ruby and Gulp approach. We use Gulp to manage the task, but actual CSS compilation is done by Ruby gems.

```
gem install bundler
bundle install
npm install
gulp
```

### Note on Zen and Compass

I've found out that the issue is Zen 5.5 is not compatible with the new compass. There are issues about it, with some patches, but none of these is approved and probably will never be.
The best solution is to rollback to the officially supported Compass version.

As we are using Gulp for the managing the task, we are unable to choose the exact version of compass to use and there can be multiple installed at once. Gulp will choose the newest version available.
We need to make sure the correct version (Compass 0.12.7) is installed and it is the only one or the newest one available.

**Steps to fix:**
run `gem list` – to see how many version of compass you have installed.
run `gem uninstall compass` and uninstall all versions.
run `gem install compass -v 0.12.7`
repeat previous step until 0.12.7 is the newest version
